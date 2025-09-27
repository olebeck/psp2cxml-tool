
#include <sys/stat.h>
#include "cxml.h"
#include "xml.h"
#include "sha1.h"


const std::vector<std::string> cxml::schema::item::NoneParent;


static std::vector<std::string> split(const std::string &s, char delim){

	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string item;

	while(getline(ss, item, delim)){
		if(!item.empty()){
			item.erase(std::remove(item.begin(), item.end(), ' '), item.end());
			elems.push_back(item);
		}
	}

	return elems;
}

static uint32_t calc_id_hash_upper4(const char *key){

	SHA1Context ctx;
	uint8_t hash[0x14];

	SHA1Reset(&ctx);
	SHA1Input(&ctx, key, strlen(key));
	SHA1Result(&ctx, hash);

	return hash[3] | (hash[2] << 8) | (hash[1] << 16) | (hash[0] << 24);
}

int cxml::compiler::register_id_table_entity(const char *key, int32_t entity_offset, uint32_t *offset){

	int res;

	std::map<std::string, uint32_t>::iterator _item = m_id_map.find(key);

	if(_item != m_id_map.end()){ // have same hash

		std::pair<const std::string, uint32_t>& _item2 = *_item;

		int32_t *_entity_offset = (int32_t *)((uintptr_t)m_idtable.GetData() + _item2.second);
		if(*_entity_offset != ~0){
            printf("Error: duplicate id '%s'\n", key);
			return -1;
		}

		*_entity_offset = entity_offset;
		*offset = _item2.second;
	}else{
		uint32_t _offset;

		res = m_idtable.append_data_raw(&entity_offset, 4, &_offset);
		if(res < 0){
			return res;
		}

		res = m_idtable.append_data_raw(key, strlen(key) + 1, NULL);
		if(res < 0){
			return res;
		}

		res = m_idtable.Align(sizeof(int));
		if(res < 0){
			return res;
		}

		m_id_map[key] = _offset;
		*offset = _offset;
	}

	return 0;
}

int cxml::compiler::register_id_table_ref(const char *key, uint32_t ref_offset, uint32_t *offset){

	int res;

	std::map<std::string, uint32_t>::iterator _item = m_id_map.find(key);

	if(_item != m_id_map.end()){ // have same hash
		std::pair<const std::string, uint32_t>& _item2 = *_item;
		*offset = _item2.second;
	}else{
		uint32_t _offset, entity_offset;

		entity_offset = ~0;

		res = m_idtable.append_data_raw(&entity_offset, 4, &_offset);
		if(res < 0){
			return res;
		}

		res = m_idtable.append_data_raw(key, strlen(key) + 1, NULL);
		if(res < 0){
			return res;
		}

		res = m_idtable.Align(sizeof(int));
		if(res < 0){
			return res;
		}

		m_id_map[key] = _offset;
		*offset = _offset;
	}

	return 0;
}

int cxml::compiler::register_hash_table(const char *key, uint32_t *offset, uint32_t *size){

	uint32_t key_hashval_upper4 = calc_id_hash_upper4(key);

	std::map<uint32_t, uint32_t>::iterator _item = m_hash_map.find(key_hashval_upper4);

	if(_item != m_hash_map.end()){ // have same hash

		std::list<std::string>::iterator _item2 = std::find(m_hash_table_originkey_list.begin(), m_hash_table_originkey_list.end(), key);

		if(_item2 == m_hash_table_originkey_list.end()){
			printf("Warning: id:%s hash key is duplicated.\n", key);
		}

		std::pair<const uint32_t, uint32_t>& _off = *_item;

		*offset = _off.second;
		*size = 4;
	}else{
		uint32_t _offset;

		int res = m_hashtable.append_data_raw(&key_hashval_upper4, 4, &_offset);
		if(res < 0){
			return res;
		}

		m_hash_map[key_hashval_upper4] = (uint32_t)(_offset / 4);

		m_hash_table_originkey_list.push_back(key);

		*offset = _offset / 4;
		*size = 4;
	}

	return 0;
}

int cxml::compiler::register_idhash_table_entity(const char *key, int32_t entity_offset, uint32_t *offset){

	int res;
	uint32_t key_hashval_upper4, _offset;

	key_hashval_upper4 = calc_id_hash_upper4(key);
	if(key_hashval_upper4 == default_idhash_invalid){
		printf("Error: this idhash '0x%x' (key = %s) is reserved for system idhash value.\n", key_hashval_upper4, key);
		return -1;
	}

	std::map<uint32_t, uint32_t>::iterator _item = m_idhash_map.find(key_hashval_upper4);

	if(_item != m_idhash_map.end()){ // have same hash

		std::pair<const uint32_t, uint32_t>& _item2 = *_item;

		int32_t *_entity_offset = (int32_t *)((uintptr_t)m_idhashtable.GetData() + _item2.second);
		if(*_entity_offset != ~0){
			printf("Error: duplicate idhash '0x%x' (key = %s)\n", key_hashval_upper4, key);
			return -1;
		}

		*_entity_offset = entity_offset;
		*offset = _item2.second;
	}else{
		uint32_t idhash[2];
		idhash[0] = entity_offset;
		idhash[1] = key_hashval_upper4;

		res = m_idhashtable.append_data_raw(idhash, sizeof(idhash), &_offset);
		if(res < 0){
			return res;
		}

		m_idhash_map[key_hashval_upper4] = _offset;
		*offset = _offset;
	}

	return 0;
}

int cxml::compiler::register_idhash_table_ref(const char *key, uint32_t ref_offset, uint32_t *offset){

	int res;
	uint32_t key_hashval_upper4, _offset;

	key_hashval_upper4 = calc_id_hash_upper4(key);

	std::map<uint32_t, uint32_t>::iterator _item = m_idhash_map.find(key_hashval_upper4);

	if(_item != m_idhash_map.end()){ // have same hash
		std::pair<const uint32_t, uint32_t>& _item2 = *_item;
		*offset = _item2.second;
	}else{
		uint32_t idhash[2];
		idhash[0] = ~0;
		idhash[1] = key_hashval_upper4;

		res = m_idhashtable.append_data_raw(idhash, sizeof(idhash), &_offset);
		if(res < 0){
			return res;
		}

		m_idhash_map[key_hashval_upper4] = _offset;
		*offset = _offset;
	}

	return 0;
}

int cxml::compiler::fileProvider_default(tinyxml2::XMLElement *tag, const char *path, cxml::stack& fileimage, void *argp){

	int res = fileimage.append_file_data(path, NULL);
	if(res < 0){
		return res;
	}

	return 0;
}

cxml::compiler::compiler(){
	SetMagic("CXML");
	SetVersion(CXML_VERSION(1, 0, 0));
	m_cxml_data = NULL;
	m_cxml_size = 0;
}

void cxml::compiler::SetMagic(const char *magic){
	memcpy(m_magic, magic, sizeof(m_magic));
}

cxml::Version cxml::compiler::SetVersion(cxml::Version version){
	cxml::Version prev_version = m_version;
	m_version = version;
	return prev_version;
}

void cxml::compiler::append_schema(const schema::item& item){
	m_schema.append(item);
}

void cxml::compiler::Reset(bool cleanCxmlData){

	if(cleanCxmlData == true){
		free(m_cxml_data);
		m_cxml_data = NULL;
		m_cxml_size = 0;
	}

	m_tree.Reset();
	m_idtable.Reset();
	m_idhashtable.Reset();
	m_stringtable.Reset();
	m_wstringtable.Reset();
	m_hashtable.Reset();
	m_intarraytable.Reset();
	m_floatarraytable.Reset();
	m_filetable.Reset();

	m_hash_table_originkey_list.clear();
	m_file_map.clear();
	m_id_map.clear();
	m_hash_map.clear();
	m_idhash_map.clear();
}

int cxml::compiler::xml_tag_check_callback(tinyxml2::XMLDocument *doc, tinyxml2::XMLElement *tag, void *argp){

	tag->SetUserData(NULL);

	compiler *pCompiler = (compiler *)argp;

	if(pCompiler->m_schema.HasItem(tag->Value()) == false){
		return -2;
	}

	cxml::schema::item& _item = pCompiler->m_schema.FindItem(tag->Value());

	if((uintptr_t)tag->Parent() != (uintptr_t)doc && _item.HasParent(tag->Parent()->Value()) == false){
		printf(
			"[%s] Invalid Parent : ",
#ifndef PSP2CXML_INVALID_PARENT_WARN
			"E"
#else
			"W"
#endif
		);

		size_t tree_deep = 0;
		tinyxml2::XMLElement *tag_curr = tag;

		while(tag_curr != NULL && doc != tag_curr->ToDocument()){
			tree_deep++;
			tag_curr = tag_curr->Parent()->ToElement();
		}

		tinyxml2::XMLElement **pList = (tinyxml2::XMLElement **)malloc(sizeof(tinyxml2::XMLElement *) * tree_deep);
		if(pList != NULL){

			tree_deep = 0;
			tag_curr = tag;

			while(tag_curr != NULL && doc != tag_curr->ToDocument()){
				pList[tree_deep++] = tag_curr;
				tag_curr = tag_curr->Parent()->ToElement();
			}

			size_t index = 0;

			while(tree_deep != 0){
				tree_deep--;
				printf("(%lld):%s", index++, pList[tree_deep]->Value());
				if(tree_deep != 0){
					printf(" -> ");
				}
			}

			free(pList);
		}else{
			printf("memory error");
		}

		printf("\n");

#ifndef PSP2CXML_INVALID_PARENT_WARN
		return -1;
#endif
	}

	const tinyxml2::XMLAttribute *attr = tag->FirstAttribute();

	while(attr != NULL){
		if(_item.HasAttr(attr->Name()) == false){
			printf("Key \"%s\" not allowed attr \"%s\"\n", tag->Value(), attr->Name());
			return -1;
		}

		attr = attr->Next();
	}

	return 0;
}

int cxml::compiler::xml_userdata_free_callback(tinyxml2::XMLDocument *doc, tinyxml2::XMLElement *tag, void *argp){
	free(tag->GetUserData());
	tag->SetUserData(NULL);
	return 0;
}

int cxml::compiler::xml_tag_preparate_file_callback(tinyxml2::XMLDocument *doc, tinyxml2::XMLElement *tag, void *argp){

	compiler *pCompiler = (compiler *)argp;

	const tinyxml2::XMLAttribute *attr = tag->FirstAttribute();

	cxml::schema::item& _item = pCompiler->m_schema.FindItem(tag->Value());

	while(attr != NULL){

		cxml::schema::item::attr& _attr = _item.FindAttr(attr->Name());

		if(_attr.GetType() == cxml::attr_type_filename){

			std::map<std::string, File>::iterator _item = pCompiler->m_file_map.find(attr->Value());
			if(_item == pCompiler->m_file_map.end()){

				uint32_t offset;
				cxml::stack fileimage;
				std::string path = pCompiler->m_base_path + "/" + attr->Value();
				pCompiler->dependencies.push_back(path);

				int res = pCompiler->m_fileProvider(tag, path.c_str(), fileimage, NULL);
				if(res < 0){
					return res;
				}

				res = pCompiler->m_filetable.append_data_raw(fileimage.GetData(), fileimage.GetSize(), &offset);
				if(res < 0){
					return res;
				}

				pCompiler->m_file_map[attr->Value()] = File(attr->Value(), offset, fileimage.GetSize());
			}
		}

		attr = attr->Next();
	}

	return 0;
}

int cxml::compiler::xml_tag_alloc_pre_callback(tinyxml2::XMLDocument *doc, tinyxml2::XMLElement *tag, void *argp){

	int res;
	uint32_t offset;
	tree_key key;
	compiler *pCompiler = (compiler *)argp;

	res = pCompiler->m_stringtable.append_string_from_utf8(tag->Value(), &offset);
	if(res < 0){
		return res;
	}

	key.name_handle            = offset;
	key.num_attributes         = 0;
	key.parent_elm_offset      = ~0;
	key.prev_elm_offset        = ~0;
	key.next_elm_offset        = ~0;
	key.first_child_elm_offset = ~0;
	key.last_child_elm_offset  = ~0;

	pre_tree_header *header = (pre_tree_header *)malloc(sizeof(pre_tree_header));
	if(header == NULL){
		return -1;
	}

	tag->SetUserData(header);

	res = pCompiler->m_tree.append_data_raw(&key, sizeof(key), &(header->offset));
	if(res < 0){
		return res;
	}

	const tinyxml2::XMLAttribute *attr = tag->FirstAttribute();

	cxml::schema::item& _item = pCompiler->m_schema.FindItem(tag->Value());

	while(attr != NULL){

		cxml::schema::item::attr& _attr = _item.FindAttr(attr->Name());

		uint32_t attr_temp[4];
		memset(attr_temp, 0, sizeof(attr_temp));

		res = pCompiler->m_stringtable.append_string_from_utf8(attr->Name(), &offset);
		if(res < 0){
			return res;
		}

		attr_temp[0] = offset;
		attr_temp[1] = _attr.GetType();

		pCompiler->m_tree.append_data_raw(attr_temp, sizeof(attr_temp), NULL);

		switch(_attr.GetType()){
		case attr_type_int:
		case attr_type_float:
			break;
		case attr_type_string:
			{
				uint32_t offset;

				int res = pCompiler->m_stringtable.append_string_from_utf8(attr->Value(), &offset);
				if(res < 0){
					return res;
				}
			}
			break;
		case attr_type_wstring:
			{
				uint32_t offset;

				int res = pCompiler->m_wstringtable.append_wstring_from_utf8(attr->Value(), &offset);
				if(res < 0){
					return res;
				}
			}
			break;
		case attr_type_hash:
		case attr_type_intarray:
		case attr_type_floatarray:
		case attr_type_filename:
		case attr_type_id:
		case attr_type_idref:
		case attr_type_idhash:
		case attr_type_idhashref:
		default:
			break;
		}


		key.num_attributes++;
		attr = attr->Next();
	}

	memcpy((void *)((uintptr_t)pCompiler->m_tree.GetData() + header->offset), &key, sizeof(key));

	return 0;
}

int cxml::compiler::xml_tag_resolve_offsets_callback(tinyxml2::XMLDocument *doc, tinyxml2::XMLElement *tag, void *argp){

	compiler *pCompiler = (compiler *)argp;
	pre_tree_header *pre_header = (pre_tree_header *)tag->GetUserData();

	tree_key *key = (tree_key *)((uintptr_t)pCompiler->m_tree.GetData() + pre_header->offset);

	if(doc != tag->Parent()){
		pre_tree_header *parent_header = (pre_tree_header *)tag->Parent()->GetUserData();
		key->parent_elm_offset = parent_header->offset;
	}

	if(tag->PreviousSiblingElement() != NULL){
		pre_tree_header *parent_header = (pre_tree_header *)tag->PreviousSiblingElement()->GetUserData();
		key->prev_elm_offset = parent_header->offset;
	}

	if(tag->NextSiblingElement() != NULL){
		pre_tree_header *parent_header = (pre_tree_header *)tag->NextSiblingElement()->GetUserData();
		key->next_elm_offset = parent_header->offset;
	}

	if(tag->FirstChildElement() != NULL){
		pre_tree_header *parent_header = (pre_tree_header *)tag->FirstChildElement()->GetUserData();
		key->first_child_elm_offset = parent_header->offset;
	}

	if(tag->LastChildElement() != NULL){
		pre_tree_header *parent_header = (pre_tree_header *)tag->LastChildElement()->GetUserData();
		key->last_child_elm_offset = parent_header->offset;
	}

	return 0;
}

int cxml::compiler::xml_tag_resolve_attr_callback(tinyxml2::XMLDocument *doc, tinyxml2::XMLElement *tag, void *argp){

	compiler *pCompiler = (compiler *)argp;

	cxml::schema::item& _item = pCompiler->m_schema.FindItem(tag->Value());

	pre_tree_header *pre_header = (pre_tree_header *)tag->GetUserData();

	tree_key *key = (tree_key *)((uintptr_t)pCompiler->m_tree.GetData() + pre_header->offset);

	int index = 0;

	const tinyxml2::XMLAttribute *attr = tag->FirstAttribute();

	while(attr != NULL){

		void *ptr = (void *)((uintptr_t)key + sizeof(*key) + index * 0x10);

		cxml::schema::item::attr& _attr = _item.FindAttr(attr->Name());

		switch(_attr.GetType()){
		case attr_type_int:
			*(int *)((uintptr_t)ptr + 0x8) = (int)strtol(attr->Value(), NULL, 10);
			break;
		case attr_type_float:
			*(float *)((uintptr_t)ptr + 0x8) = strtof(attr->Value(), NULL);
			break;
		case attr_type_string:
			{
				uint32_t offset;

				int res = pCompiler->m_stringtable.append_string_from_utf8(attr->Value(), &offset);
				if(res < 0){
					return res;
				}

				*(int *)((uintptr_t)ptr + 0x8) = offset;
				*(int *)((uintptr_t)ptr + 0xC) = strlen(attr->Value());
			}
			break;
		case attr_type_wstring:
			{
				uint32_t offset;

				int res = pCompiler->m_wstringtable.append_wstring_from_utf8(attr->Value(), &offset);
				if(res < 0){
					return res;
				}

				*(int *)((uintptr_t)ptr + 0x8) = offset >> 1;
				*(int *)((uintptr_t)ptr + 0xC) = strlen(attr->Value()) << 1;
			}
			break;
		case attr_type_hash:
			{
				uint32_t offset, size;
				pCompiler->register_hash_table(attr->Value(), &offset, &size);

				*(int *)((uintptr_t)ptr + 0x8) = offset;
				*(int *)((uintptr_t)ptr + 0xC) = size;
			}
			break;
		case attr_type_intarray:
			{
				uint32_t offset;
				cxml::stack intarray;
				std::vector<std::string> result = split(std::string(attr->Value()), ',');

				for(std::vector<std::string>::iterator it=result.begin();it!=result.end();it++){
					std::string& v = *it;

					char *end;
					int vi = strtol(v.c_str(), &end, 10);

					if((v.length() - (end - v.c_str())) != 0){
						printf("has illegal float value. (%s)\n", v.c_str());
						return -1;
					}

					intarray.append_data_raw(&vi, sizeof(vi), NULL);
				}

				int res = pCompiler->m_intarraytable.Align(sizeof(int));
				if(res < 0){
					return -1;
				}

				res = pCompiler->m_intarraytable.append_intarray((const int *)intarray.GetData(), intarray.GetSize() / sizeof(int), &offset);
				if(res < 0){
					return -1;
				}

				*(int *)((uintptr_t)ptr + 0x8) = offset / 4;
				*(int *)((uintptr_t)ptr + 0xC) = intarray.GetSize() / 4;
			}
			break;
		case attr_type_floatarray:
			{
				uint32_t offset;
				cxml::stack floatarray;
				std::vector<std::string> result = split(std::string(attr->Value()), ',');

				for(std::vector<std::string>::iterator it=result.begin();it!=result.end();it++){
					std::string& v = *it;

					char *end;
					float vf = strtof(v.c_str(), &end);

					if((v.length() - (end - v.c_str())) != 0){
						printf("has illegal float value. (%s)\n", v.c_str());
						return -1;
					}

					floatarray.append_data_raw(&vf, sizeof(vf), NULL);
				}

				int res = pCompiler->m_floatarraytable.Align(sizeof(float));
				if(res < 0){
					return -1;
				}

				res = pCompiler->m_floatarraytable.append_floatarray((const float *)floatarray.GetData(), floatarray.GetSize() / sizeof(float), &offset);
				if(res < 0){
					return -1;
				}

				*(int *)((uintptr_t)ptr + 0x8) = offset / 4;
				*(int *)((uintptr_t)ptr + 0xC) = floatarray.GetSize() / 4;
			}
			break;
		case attr_type_filename:
			{
				std::map<std::string, File>::iterator _item = pCompiler->m_file_map.find(attr->Value());
				std::pair<const std::string, File> _pair = *_item;

				*(int *)((uintptr_t)ptr + 0x8) = _pair.second.m_offset;
				*(int *)((uintptr_t)ptr + 0xC) = _pair.second.m_size;
			}
			break;
		case attr_type_id:
			{
				uint32_t offset;
				if(pCompiler->register_id_table_entity(attr->Value(), pre_header->offset, &offset) < 0){
					return -1;
				}

				*(int *)((uintptr_t)ptr + 0x8) = offset;
			}
			break;
		case attr_type_idref:
			{
				uint32_t offset;
				if(pCompiler->register_id_table_ref(attr->Value(), pre_header->offset + sizeof(*key) + index * 0x10, &offset) < 0){
					return -1;
				}

				*(int *)((uintptr_t)ptr + 0x8) = offset;
			}
			break;
		case attr_type_idhash:
			{
				uint32_t offset;
				if(pCompiler->register_idhash_table_entity(attr->Value(), pre_header->offset, &offset) < 0){
					return -1;
				}

				*(int *)((uintptr_t)ptr + 0x8) = offset;
			}
			break;
		case attr_type_idhashref:
			{
				uint32_t offset;
				if(pCompiler->register_idhash_table_ref(attr->Value(), pre_header->offset + sizeof(*key) + index * 0x10, &offset) < 0){
					return -1;
				}

				*(int *)((uintptr_t)ptr + 0x8) = offset;
			}
			break;
		default:
			break;
		}

		attr = attr->Next();
		index++;
	}

	return 0;
}

int cxml::compiler::CompileXml(const char *xml_path, FileProvider fileProvider){

	int res;

	Reset(true);

	{
		const char *path_base = strrchr(xml_path, '/');
		if(path_base == NULL){
			path_base = strrchr(xml_path, '\\');
		}

		if(path_base == NULL){
			path_base = strrchr(xml_path, ':');
		}

		if(path_base == NULL){
			return -1;
		}

		size_t path_len = path_base - xml_path;

		char *temp_path = (char *)malloc(path_len + 1);

		memcpy(temp_path, xml_path, path_len);
		temp_path[path_len] = 0;

		m_base_path = temp_path;

		free(temp_path);
	}

	m_fileProvider = fileProvider;

	tinyxml2::XMLDocument doc;

	res = doc.LoadFile(xml_path);
	if(res != tinyxml2::XMLError::XML_SUCCESS){
		printf("Parse xml failed. (%s)\n", xml_path);
		return -1;
	}

	res = ProcessXml(&doc, xml_tag_check_callback, this);
	if(res < 0){
		printf("Check xml tag failed. (%s)\n", xml_path);
		return res;
	}

	do {
		res = ProcessXml(&doc, xml_tag_preparate_file_callback, this);
		if(res < 0){
			printf("Preparate file failed. (%s)\n", xml_path);
			break;
		}

		res = ProcessXml(&doc, xml_tag_alloc_pre_callback, this);
		if(res < 0){
			printf("Alloc tag failed. (%s)\n", xml_path);
			break;
		}

		res = ProcessXml(&doc, xml_tag_resolve_offsets_callback, this);
		if(res < 0){
			printf("Resolve offsets failed. (%s)\n", xml_path);
			break;
		}

		res = ProcessXml(&doc, xml_tag_resolve_attr_callback, this);
		if(res < 0){
			printf("Resolve attr failed. (%s)\n", xml_path);
			break;
		}

		// required non aligned size
		uint32_t tree_size            = m_tree.GetSize();
		uint32_t idtable_size         = m_idtable.GetSize();
		uint32_t idhashtable_size     = m_idhashtable.GetSize();
		uint32_t stringtable_size     = m_stringtable.GetSize();
		uint32_t wstringtable_size    = m_wstringtable.GetSize();
		uint32_t hashtable_size       = m_hashtable.GetSize();
		uint32_t intarraytable_size   = m_intarraytable.GetSize();
		uint32_t floatarraytable_size = m_floatarraytable.GetSize();
		uint32_t filetable_size       = m_filetable.GetSize();

		res = m_tree.Align(0x10);
		if(res < 0){
			printf("Align tree failed. (%s)\n", xml_path);
			break;
		}

		res = m_idtable.Align(0x10);
		if(res < 0){
			printf("Align idtable failed. (%s)\n", xml_path);
			break;
		}

		res = m_idhashtable.Align(0x10);
		if(res < 0){
			printf("Align idhashtable failed. (%s)\n", xml_path);
			break;
		}

		res = m_stringtable.Align(0x10);
		if(res < 0){
			printf("Align stringtable failed. (%s)\n", xml_path);
			break;
		}

		res = m_wstringtable.Align(0x10);
		if(res < 0){
			printf("Align wstringtable failed. (%s)\n", xml_path);
			break;
		}

		res = m_hashtable.Align(0x10);
		if(res < 0){
			printf("Align hashtable failed. (%s)\n", xml_path);
			break;
		}

		res = m_intarraytable.Align(0x10);
		if(res < 0){
			printf("Align intarraytable failed. (%s)\n", xml_path);
			break;
		}

		res = m_floatarraytable.Align(0x10);
		if(res < 0){
			printf("Align floatarraytable failed. (%s)\n", xml_path);
			break;
		}

/*
		res = m_filetable.Align(0x10);
		if(res < 0){
			printf("Align filetable failed. (%s)\n", xml_path);
			break;
		}
*/

		Header cxml_header;
		memset(&cxml_header, 0, sizeof(cxml_header));
		memcpy(cxml_header.magic, m_magic, 4);
		cxml_header.version                = m_version;
		cxml_header.tree_offset            = sizeof(cxml_header);
		cxml_header.tree_size              = tree_size;
		cxml_header.idtable_offset         = cxml_header.tree_offset + m_tree.GetSize();
		cxml_header.idtable_size           = idtable_size;
		cxml_header.idhashtable_offset     = cxml_header.idtable_offset + m_idtable.GetSize();
		cxml_header.idhashtable_size       = idhashtable_size;
		cxml_header.stringtable_offset     = cxml_header.idhashtable_offset + m_idhashtable.GetSize();
		cxml_header.stringtable_size       = stringtable_size;
		cxml_header.wstringtable_offset    = cxml_header.stringtable_offset + m_stringtable.GetSize();
		cxml_header.wstringtable_size      = wstringtable_size;
		cxml_header.hashtable_offset       = cxml_header.wstringtable_offset + m_wstringtable.GetSize();
		cxml_header.hashtable_size         = hashtable_size;
		cxml_header.intarraytable_offset   = cxml_header.hashtable_offset + m_hashtable.GetSize();
		cxml_header.intarraytable_size     = intarraytable_size;
		cxml_header.floatarraytable_offset = cxml_header.intarraytable_offset + m_intarraytable.GetSize();
		cxml_header.floatarraytable_size   = floatarraytable_size;
		cxml_header.filetable_offset       = cxml_header.floatarraytable_offset + m_floatarraytable.GetSize();
		cxml_header.filetable_size         = filetable_size;

		m_cxml_size = cxml_header.filetable_offset + cxml_header.filetable_size;
		m_cxml_data = malloc(m_cxml_size);
		if(m_cxml_data == NULL){
			printf("Alloc CXML buffer failed. (%s)\n", xml_path);
			res = -1;
			break;
		}

		memcpy(m_cxml_data, &cxml_header, sizeof(cxml_header));
		memcpy((void *)((uintptr_t)m_cxml_data + cxml_header.tree_offset), m_tree.GetData(), m_tree.GetSize());
		memcpy((void *)((uintptr_t)m_cxml_data + cxml_header.idtable_offset), m_idtable.GetData(), m_idtable.GetSize());
		memcpy((void *)((uintptr_t)m_cxml_data + cxml_header.idhashtable_offset), m_idhashtable.GetData(), m_idhashtable.GetSize());
		memcpy((void *)((uintptr_t)m_cxml_data + cxml_header.stringtable_offset), m_stringtable.GetData(), m_stringtable.GetSize());
		memcpy((void *)((uintptr_t)m_cxml_data + cxml_header.wstringtable_offset), m_wstringtable.GetData(), m_wstringtable.GetSize());
		memcpy((void *)((uintptr_t)m_cxml_data + cxml_header.hashtable_offset), m_hashtable.GetData(), m_hashtable.GetSize());
		memcpy((void *)((uintptr_t)m_cxml_data + cxml_header.intarraytable_offset), m_intarraytable.GetData(), m_intarraytable.GetSize());
		memcpy((void *)((uintptr_t)m_cxml_data + cxml_header.floatarraytable_offset), m_floatarraytable.GetData(), m_floatarraytable.GetSize());
		memcpy((void *)((uintptr_t)m_cxml_data + cxml_header.filetable_offset), m_filetable.GetData(), m_filetable.GetSize());

		res = 0;
	} while(0);

	ProcessXml(&doc, xml_userdata_free_callback, this);

	Reset(false);

	return res;
}

int cxml::compiler::GetCxmlData(stack& cxml_image){

	int res;

	if(m_cxml_data == NULL || m_cxml_size == 0){
		return -1;
	}

	res = cxml_image.append_data_raw(m_cxml_data, m_cxml_size, NULL);
	if(res < 0){
		return res;
	}

	return 0;
}

int cxml::compiler::Save(const char *path){

	int res;
	FILE *fp;

	if(m_cxml_data == NULL || m_cxml_size == 0){
		return -1;
	}

	fp = fopen(path, "wb");
	if(fp == NULL){
		return -1;
	}

	do {
		res = fwrite(m_cxml_data, m_cxml_size, 1, fp);
		if(res != 1){
			res = -1;
			break;
		}

		res = 0;
	} while(0);

	fclose(fp);
	fp = NULL;

	return res;
}


int cxml::compiler::SaveDependencies(const char *dst_path, const char *dep_path){

	int res;
	FILE *fp;

	fp = fopen(dep_path, "wb");
	if(fp == NULL){
		return -1;
	}

	res = fprintf(fp, "%s: ", dst_path);
	if(res == 0){
		fclose(fp);
		return -1;
	}

	for(const auto& file_path : this->dependencies) {
		res = fprintf(fp, "%s ", file_path.c_str());
		if(res == 0){
			res = -1;
			break;
		}
		res = 0;
	}

	fclose(fp);
	fp = NULL;
	return res;
}