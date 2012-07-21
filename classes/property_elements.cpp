#include "../main_header.h"

Property_elements::Property_elements() {
	
	
	
}

Property_elements::~Property_elements() {
	
	
	
	
}

void Property_elements::thumbnail(int property_id, string output) {
	
	string thumbnail;
	
	if(output == "live")
		thumbnail.append(headers());
	
	thumbnail.append("<div class=\'thumbnail\'>\n");

	// header tag
	thumbnail.append("<h1>");
	thumbnail.append(get_string_value(property_id, "name"));
	thumbnail.append("</h1>");
	
	// open listing tag and add url
	thumbnail.append("<a href=\'");
	thumbnail.append(listing_url(property_id));
	thumbnail.append("\'>\n");//close first piece of anchor
	
	//add thumbnail image inside!
	thumbnail.append("\n<div class=\'image\'>");
	thumbnail.append(listing_thumbnail_image(property_id));
	thumbnail.append("\n</div>\n");
	
	//add thumbnail_blurb
	thumbnail.append("\n<div class=\'blurb\'>\n");
	thumbnail.append(get_string_value(property_id, "thumbnail_blurb"));
	thumbnail.append("\n</div>\n");
	
	// end anchor tag
	thumbnail.append("\n</a>");
	// end div tag
	thumbnail.append("\n</div>");
	
	cout << thumbnail;
	
}

string Property_elements::listing_url(int property_id) {
	
	string listing_url;
	listing_url.append(configuration.get_site_url());
	listing_url.append("listing/");
	listing_url.append(helper.integer_to_string(property_id));
	
	return listing_url;
}

string Property_elements::listing_thumbnail_image(int property_id) {
	
	string url, image_tag;
	
	url.append(configuration.get_base_url());
	url.append(get_string_value(property_id, "thumbnail_url"));
	
	image_tag.append("\n<img alt=\'");
	image_tag.append(get_string_value(property_id, "name"));
	image_tag.append("\' src=\'");
	image_tag.append(url);
	image_tag.append("\' />");//end image tag
	
	return image_tag;
}

string Property_elements::headers() {
	
	cout << "Content-type: text/html" << endl << endl;
	
}