#pragma once
#include"const.h"
struct SectionInfo {
	SectionInfo() {}
	
	
	~SectionInfo() { section_datas.clear(); }
	
	
	SectionInfo(const SectionInfo& str) {
		section_datas = str.section_datas;
	}
	
	
	SectionInfo& operator=(const SectionInfo& scr) {
		if (&scr == this) {
			return *this;
		}
		this->section_datas = scr.section_datas;
		return *this;
	}
	std::string operator[](const std::string key) {
		if (section_datas.find(key) == section_datas.end()) {
			return "";
		}
		else {
			return section_datas[key];
		}
	}

	
	std::map<std::string, std::string> section_datas;
};
class ConfigMgr
{
public:
	~ConfigMgr() { config_map.clear(); }
	//this->config_map = src.config_map;
	 ConfigMgr(const ConfigMgr& src)  = delete;


	 static ConfigMgr& GetConfigMgr() {
		 static ConfigMgr con_mgr;
		 return con_mgr;
	 }

	/*		if (&src == this) {
			return *this;
		}
		this->config_map = src.config_map;
		return *this;*/
	ConfigMgr& operator=(const ConfigMgr& src) = delete;

	SectionInfo operator[](const std::string section) {
		if (config_map.find(section) == config_map.end()) {
			return SectionInfo();
		}
		return config_map[section];
	}
	ConfigMgr();
private:
	
	std::map<std::string, SectionInfo> config_map;
};

