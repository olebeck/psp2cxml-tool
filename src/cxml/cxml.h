
#ifndef _CXML_H_
#define _CXML_H_

#include <sys/stat.h>
#include <string.h>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <zlib.h>
#include "tinyxml2.h"


#define CXML_VERSION(major, minor, rev) (((major) << 8) | (((minor) << 4) & 0xF0) | ((rev) & 0xF))


namespace cxml {
	class stack { // my class
	public:
		stack(){
			m_data = malloc(0x4000);
			m_size = 0;
			m_current_size = 0x4000;
			m_ResetHandler = NULL;
			m_argp = NULL;
		}

		~stack(){
			Reset();
		}

		void Reset(void){
			free(m_data);

			m_data = NULL;
			m_size = 0;
			m_current_size = 0;

			if(m_ResetHandler != NULL){
				m_ResetHandler(m_argp);
			}
		}

		int append_data_raw(const void *data, size_t size, uint32_t *offset){

			int res;

			res = GrowCheck(size);
			if(res < 0){
				return res;
			}

			int prev_size = m_size;

			memcpy((void *)((uintptr_t)m_data + m_size), data, size);
			m_size += size;

			if(offset != NULL){
				*offset = prev_size; // as offset
			}

			return 0;
		}

		int append_data_raw(int data, size_t size, uint32_t *offset){

			int res;

			res = GrowCheck(size);
			if(res < 0){
				return res;
			}

			int prev_size = m_size;

			memset((void *)((uintptr_t)m_data + m_size), data, size);
			m_size += size;

			if(offset != NULL){
				*offset = prev_size; // as offset
			}

			return 0;
		}

		int append_file_data(const char *file_path, uint32_t *offset){

			int res;
			struct stat _stat;
			FILE *fp;

			res = stat(file_path, &_stat);
			if(res != 0){
				return -1;
			}

			res = GrowCheck(_stat.st_size);
			if(res < 0){
				return res;
			}

			fp = fopen(file_path, "rb");

			do {
				res = fread((void *)((uintptr_t)m_data + m_size), _stat.st_size, 1, fp);
				if(res != 1){
					res = -1;
					break;
				}

				if(offset != NULL){
					*offset = m_size; // as offset
				}

				m_size += _stat.st_size;

				res = 0;
			} while(0);

			fclose(fp);

			return res;
		}

		int Align(size_t align){
			return append_data_raw(0, ((m_size + (align - 1)) & ~(align - 1)) - m_size, NULL);
		}

		int Compress(void){

			int res;
			long unsigned int compress_dst_size = (m_size << 1) + 12 + 0x1000;
			void *compress_dst = malloc(compress_dst_size);
			if(compress_dst == NULL){
				return -1;
			}

			do {
				res = compress((Bytef *)compress_dst, &compress_dst_size, (const Bytef *)m_data, m_size);
				if(res < 0){
					break;
				}

				void *_t_dst = malloc((compress_dst_size + (0x4000 - 1)) & ~(0x4000 - 1));
				if(_t_dst == NULL){
					res = -1;
					break;
				}

				memcpy(_t_dst, compress_dst, compress_dst_size);

				free(compress_dst);
				free(m_data);

				m_data = _t_dst;
				m_size = compress_dst_size;
				m_current_size = (m_size + (0x4000 - 1)) & ~(0x4000 - 1);

				return 0;
			} while(0);

			free(compress_dst);
			compress_dst = NULL;

			return res;
		}

		void *GetData(void){
			return m_data;
		}

		size_t GetSize(void){
			return m_size;
		}

		stack& operator=(const stack& rh){

			free(m_data);

			m_data = malloc(rh.m_current_size);
			if(m_data == NULL){
				__builtin_trap();
			}

			m_size = rh.m_size;
			m_current_size = rh.m_current_size;

			memcpy(m_data, rh.m_data, m_size);

			return *this;
		}

		typedef void (* ResetHandler)(void *argp);

		void SetResetHandler(ResetHandler handler, void *argp){
			m_ResetHandler = handler;
			m_argp = argp;
		}

	private:
		int GrowCheck(size_t size){
			if((m_size + size) > m_current_size){

				size_t req_size = m_current_size + 0x4000;

				if((m_size + size) > req_size){
					req_size = ((m_size + size) + (0x4000 - 1)) & ~(0x4000 - 1);
				}

				void *temp = malloc(req_size);
				if(temp == NULL){
					return -1;
				}

				memcpy(temp, m_data, m_size);

				free(m_data);
				m_data = temp;
				m_current_size = req_size;
			}

			return 0;
		}

		void *m_data;
		size_t m_size;
		size_t m_current_size;
		ResetHandler m_ResetHandler;
		void *m_argp;
	};

	class string_stack : public stack {
	public:
		string_stack(){
			SetResetHandler(resetHandler, this);
		}

		~string_stack(){
		}

		int append_string_from_utf8(const char *data, uint32_t *offset){

			int res;
			uint32_t _offset;
			stack _stack;

			std::map<std::string, uint32_t>::iterator _item = m_cache.find(data);

			if(_item != m_cache.end()){ // have same hash
				std::pair<const std::string, uint32_t>& _item2 = *_item;

				if(offset != NULL){
					*offset = _item2.second;
				}

				return 0;
			}

			res = append_data_raw(data, strlen(data) + 1, &_offset);
			if(res < 0){
				return res;
			}

			m_cache[data] = _offset;

			if(offset != NULL){
				*offset = _offset;
			}

			return 0;
		}

	private:
		static void resetHandler(void *argp){
			string_stack *stack = (string_stack *)argp;
			stack->m_cache.clear();
		}

		std::map<std::string, uint32_t> m_cache;
	};

	class wstring_stack : public stack {
	public:
		wstring_stack(){
			SetResetHandler(resetHandler, this);
		}

		~wstring_stack(){
		}

		int append_wstring_from_utf8(const char *data, uint32_t *offset){

			int res;
			stack _stack;
			uint32_t _offset;
			wchar_t utf16;
			const char *orig_data = data;

			std::map<std::string, uint32_t>::iterator _item = m_cache.find(data);

			if(_item != m_cache.end()){ // have same hash
				std::pair<const std::string, uint32_t>& _item2 = *_item;

				if(offset != NULL){
					*offset = _item2.second;
				}

				return 0;
			}

			while(*data != 0){
				if((*data & 0x80) == 0x00){
					utf16 = data[0];
					data += 1;
				}else if((*data & 0xC0) == 0x80){ // hmm?
					// utf16 = *data;
					printf("unexpected char : %X\n", *data);
					data += 1;
				}else if((*data & 0xE0) == 0xC0){
					utf16 = ((data[0] & 0x1F) << 6) | (data[1] & 0x3F);
					data += 2;
				}else if((*data & 0xF0) == 0xE0){
					utf16 = ((data[0] & 0xF) << 12) | ((data[1] & 0x3F) << 6) | (data[2] & 0x3F);
					data += 3;
				}

				res = _stack.append_data_raw(&utf16, sizeof(utf16), NULL);
				if(res < 0){
					return res;
				}
			}

			utf16 = 0;
			res = _stack.append_data_raw(&utf16, sizeof(utf16), NULL);
			if(res < 0){
				return res;
			}

			res = append_data_raw(_stack.GetData(), _stack.GetSize(), &_offset);
			if(res < 0){
				return res;
			}

			m_cache[orig_data] = _offset;

			if(offset != NULL){
				*offset = _offset;
			}

			return 0;
		}

	private:
		static void resetHandler(void *argp){
			wstring_stack *stack = (wstring_stack *)argp;
			stack->m_cache.clear();
		}

		std::map<std::string, uint32_t> m_cache;
	};

	class intarray_stack : public stack {
	public:
		intarray_stack(){
		}

		~intarray_stack(){
		}

		int append_intarray(const int *data, uint32_t count, uint32_t *offset){

			int res;
			uint32_t _offset;

			if(count == 0){
				return -1;
			}

			const int *inter_array = (const int *)GetData();
			uint32_t inter_count = (uint32_t)GetSize() / sizeof(int);

			if(inter_count >= count){

				uint32_t test_count = (inter_count - count) + 1;

				for(uint32_t i=0;i<test_count;i++){
					if(memcmp(data, &(inter_array[i]), count * sizeof(int)) == 0){
						if(offset != NULL){
							*offset = i * sizeof(int);
						}

						return 0;
					}
				}
			}

			res = append_data_raw(data, count * sizeof(int), &_offset);
			if(res < 0){
				return res;
			}

			if(offset != NULL){
				*offset = _offset;
			}

			return 0;
		}

	private:
	};

	class floatarray_stack : public stack {
	public:
		floatarray_stack(){
		}

		~floatarray_stack(){
		}

		int append_floatarray(const float *data, uint32_t count, uint32_t *offset){

			int res;
			uint32_t _offset;

			if(count == 0){
				return -1;
			}

			const float *inter_array = (const float *)GetData();
			uint32_t inter_count = (uint32_t)GetSize() / sizeof(float);

			if(inter_count >= count){

				uint32_t test_count = (inter_count - count) + 1;

				for(uint32_t i=0;i<test_count;i++){
					if(memcmp(data, &(inter_array[i]), count * sizeof(float)) == 0){
						if(offset != NULL){
							*offset = i * sizeof(float);
						}

						return 0;
					}
				}
			}

			res = append_data_raw(data, count * sizeof(float), &_offset);
			if(res < 0){
				return res;
			}

			if(offset != NULL){
				*offset = _offset;
			}

			return 0;
		}

	private:
	};

	class schema {
	public:
		class item {
		public:
			class search {
			public:
				search(const char *pKey){
					m_target = pKey;
				}

				bool operator()(const item& _item) const {
					return strcmp(m_target.c_str(), _item.m_key.c_str()) == 0;
				}

				std::string m_target;
			};

			class attr {
			public:
				class search {
				public:
					search(const char *pKey){
						m_target = pKey;
					}

					bool operator()(const attr& _attr) const {
						return strcmp(m_target.c_str(), _attr.m_key.c_str()) == 0;
					}

					std::string m_target;
				};

				attr(const char *pKey, int type){
					m_key = pKey;
					m_type = type;
				}

				~attr(){
				}

				int GetType(void){
					return m_type;
				}

			private:
				std::string m_key;
				int m_type;
			};

			item(const char *pKey, const std::vector<std::string>& pParent, const std::vector<attr>& attr){

				m_key = pKey;

				if(&pParent != &NoneParent){
					m_parent = pParent;
				}

				m_attr = attr;
			}

			~item(){
			}

			bool HasParent(const char *parent){
				return std::find(m_parent.begin(), m_parent.end(), parent) != m_parent.end();
			}

			bool HasAttr(const char *key){
				std::vector<attr>::iterator _attr = std::find_if(m_attr.begin(), m_attr.end(), attr::search(key));

				if(_attr == m_attr.end()){
					return false;
				}

				return true;
			}

			attr& FindAttr(const char *key){
				std::vector<attr>::iterator _attr = std::find_if(m_attr.begin(), m_attr.end(), attr::search(key));
				return *_attr;
			}

			static const std::vector<std::string> NoneParent;

		private:
			std::string m_key;
			std::vector<std::string> m_parent;
			std::vector<attr> m_attr;
		};

		schema(){
		}

		~schema(){
		}

		void append(const item& item){
			m_item.push_back(item);
		}

		bool HasItem(const char *key){
			std::list<item>::iterator _item = std::find_if(m_item.begin(), m_item.end(), item::search(key));

			if(_item == m_item.end()){
				return false;
			}

			return true;
		}

		item& FindItem(const char *key){
			std::list<item>::iterator _item = std::find_if(m_item.begin(), m_item.end(), item::search(key));
			return *_item;
		}

	private:
		std::list<item> m_item;
	};

	typedef struct _Header {
		char magic[4];
		int32_t version;
		int32_t tree_offset;
		int32_t tree_size;
		int32_t idtable_offset;
		int32_t idtable_size;
		int32_t idhashtable_offset;
		int32_t idhashtable_size;
		int32_t stringtable_offset;
		int32_t stringtable_size;
		int32_t wstringtable_offset;
		int32_t wstringtable_size;
		int32_t hashtable_offset;
		int32_t hashtable_size;
		int32_t intarraytable_offset;
		int32_t intarraytable_size;
		int32_t floatarraytable_offset;
		int32_t floatarraytable_size;
		int32_t filetable_offset;
		int32_t filetable_size;
	} Header;

	typedef int Version;

	enum {
		attr_type_int        = 1,
		attr_type_float      = 2,
		attr_type_string     = 3,
		attr_type_wstring    = 4,
		attr_type_hash       = 5,
		attr_type_intarray   = 6,
		attr_type_floatarray = 7,
		attr_type_filename   = 8,
		attr_type_id         = 9,
		attr_type_idref      = 10,
		attr_type_idhash     = 11,
		attr_type_idhashref  = 12
	};

	class compiler {
	public:
		typedef int (* FileProvider)(tinyxml2::XMLElement *tag, const char *path, stack& fileimage, void *argp);

		compiler();
		~compiler(){
			free(m_cxml_data);
			m_cxml_data = NULL;
		}

		void SetMagic(const char *magic);
		Version SetVersion(Version version);

		void append_schema(const schema::item& item);

		int CompileXml(const char *xml_path, FileProvider fileProvider = fileProvider_default);
		int GetCxmlData(stack& cxml_image);
		int Save(const char *path);
		int SaveDependencies(const char *dst_path, const char *dep_path);

	private:
		enum {
			default_idhash_invalid = 0
		};

		typedef struct _tree_key {
			int32_t name_handle;
			int32_t num_attributes;
			int32_t parent_elm_offset;
			int32_t prev_elm_offset;
			int32_t next_elm_offset;
			int32_t first_child_elm_offset;
			int32_t last_child_elm_offset;
		} tree_key;

		typedef struct _pre_tree_header {
			uint32_t offset;
		} pre_tree_header;

		int register_hash_table(const char *key, uint32_t *offset, uint32_t *size);
    	int register_id_table_entity(const char *key, int32_t entity_offset, uint32_t *offset);
    	int register_id_table_ref(const char *key, uint32_t ref_offset, uint32_t *offset);
		int register_idhash_table_entity(const char *key, int32_t entity_offset, uint32_t *offset);
		int register_idhash_table_ref(const char *key, uint32_t ref_offset, uint32_t *offset);

		static int fileProvider_default(tinyxml2::XMLElement *tag, const char *path, stack& fileimage, void *argp);

		static int xml_tag_check_callback(tinyxml2::XMLDocument *doc, tinyxml2::XMLElement *tag, void *argp);
		static int xml_userdata_free_callback(tinyxml2::XMLDocument *doc, tinyxml2::XMLElement *tag, void *argp);
		static int xml_tag_preparate_file_callback(tinyxml2::XMLDocument *doc, tinyxml2::XMLElement *tag, void *argp);
		static int xml_tag_alloc_pre_callback(tinyxml2::XMLDocument *doc, tinyxml2::XMLElement *tag, void *argp);
		static int xml_tag_resolve_offsets_callback(tinyxml2::XMLDocument *doc, tinyxml2::XMLElement *tag, void *argp);
		static int xml_tag_resolve_attr_callback(tinyxml2::XMLDocument *doc, tinyxml2::XMLElement *tag, void *argp);

		void Reset(bool cleanCxmlData = true);

		class File {
		public:
			File(){
				m_path = ":invalid:";
				m_offset = 0;
				m_size = 0;
			}

			File(const char *str, uint32_t offset, uint32_t size){
				m_path = str;
				m_offset = offset;
				m_size = size;
			}

			~File(){
			}

			bool operator==(const char *str){
				return strcmp(m_path.c_str(), str) == 0;
			}

			bool operator!=(const char *str){
				return !(*this == str);
			}

			std::string m_path;
			uint32_t m_offset;
			uint32_t m_size;
		};

		char m_magic[4];
		Version m_version;
		schema m_schema;

		std::string m_base_path;
		FileProvider m_fileProvider;

		stack m_tree;
		stack m_idtable;
		stack m_idhashtable;
		string_stack m_stringtable;
		wstring_stack m_wstringtable;
		stack m_hashtable;
		intarray_stack m_intarraytable;
		floatarray_stack m_floatarraytable;
		stack m_filetable;
		std::list<std::string> m_hash_table_originkey_list;
		std::map<std::string, File> m_file_map;
		std::map<std::string, uint32_t> m_id_map;
		std::map<uint32_t, uint32_t> m_hash_map;
		std::map<uint32_t, uint32_t> m_idhash_map;
		void *m_cxml_data;
		size_t m_cxml_size;

		std::vector<std::string> dependencies;
	};
}


#endif /* _CXML_H_ */
