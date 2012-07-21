#!/bin/bash

# make -f search_module.make;
# cp main.out /usr/local/apache2/cgi-bin/search.cgi


file_name=$(date +"%m_%d_%H_%I".zip); #month_day_hour_minute.zip

permanent_archive="../archive/search_module_archive_$file_name";
zip -r $permanent_archive *; 



