#include "../main_header.h"

Configuration::Configuration() {
	
	set_database_configuration();
	set_search_categories();
	set_urls("local");
}

Configuration::Configuration(string type) {
	if(type == "live")
		set_urls("live");
	else
		set_urls("local");
		
	set_database_configuration();
	set_search_categories();
}

Configuration::~Configuration() {
	
	
	
	
}

void Configuration::set_database_configuration() {
	
	host = "localhost";
	username = "morehousej09";
	password = "Moeller12";
	database = "prospero";
}

void Configuration::set_search_categories() {
	
	search_categories.push_back("address");
	search_categories.push_back("location");
	search_categories.push_back("meta_description");
	search_categories.push_back("name");
	search_categories.push_back("meta_keywords");
	search_categories.push_back("property_content");
	search_categories.push_back("type_category");
	search_categories.push_back("location_category");
}

void Configuration::set_urls(string type) {
	
	if(type == "live") {

		base_url = "http://localhost:8888/prospero/current/";
		site_url = "http://localhost:8888/prospero/current/index.php/";
	}
	
	else if (type == "local") {
		
		base_url = "http://localhost:8888/prospero/current/";
		site_url = "http://localhost:8888/prospero/current/index.php/";
	}
	
	
}

string Configuration::get_username() {
	
	return username;
	
}

string Configuration::get_password() {
	
	return password;
	
}


string Configuration::get_host() {
	
	return host;
}

string Configuration::get_database() {
	
	return database;

}

string Configuration::get_base_url() {
	
	return base_url;
	
}

string Configuration::get_site_url() {
	
	return site_url;
}