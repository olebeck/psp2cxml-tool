
#include "rco.h"
#include <unistd.h>

int psp2cxml_tool(const std::string& src, const std::string& dst, const std::string& dep){

	int res;
	rco::compiler compiler;

	res = compiler.Compile(src.c_str());
	if(res < 0){
		printf("Compile 0x%X\n", res);
		return res;
	}

	res = compiler.Save(dst.c_str());
	if(res < 0){
		printf("Save 0x%X\n", res);
		return res;
	}

	if(dep.size() > 0) {
		res = compiler.SaveDependencies(dst.c_str(), dep.c_str());
		if(res < 0){
			printf("SaveDependencies 0x%X\n", res);
			return res;
		}
	}

	return 0;
}

void print_usage() {
	printf("usage: psp2cxml-tool [-d dependency_output.d] [-o sample_plugin.rco] ./sample_plugin.xml\n");
}

int main(int argc, char *argv[]) {

	std::string dep_path;
	std::string dst_path;
	std::string src_path;

	int opt;
	while((opt = getopt(argc, argv, "d:o:")) != -1) {
		switch (opt) {
            case 'd':
                dep_path = optarg;
                break;
			case 'o':
				dst_path = optarg;
				break;
            case '?':
                print_usage();
                return EXIT_FAILURE;
            default:
                break;
        }
	}

	int non_option_args = argc - optind;
	if (non_option_args != 1) {
        print_usage();
        return EXIT_FAILURE;
    }
	src_path = argv[optind];

	if(dst_path.size() == 0) {
		int filename_length = src_path.size();
		const char *ext = strrchr(src_path.c_str(), '.');
		if (ext != NULL && strcmp(ext, ".xml") == 0) {
			filename_length -= 4;
		}
		dst_path.assign(src_path, filename_length);
		dst_path += ".rco";
	}

	int res;
	res = psp2cxml_tool(src_path, dst_path, dep_path);
	if(res < 0){
		printf("psp2cxml_tool 0x%X\n", res);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
