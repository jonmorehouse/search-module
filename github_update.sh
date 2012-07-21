#!/bin/bash

# This script is used to commit this project on github using my own personal github folder
# I have all of my github repos in one place ~Documents/github so that I don't have to worry about versioning 
# 	or worrying about the problems that it causes on upload

# Files to upload:
	# resources/javascript
	# resources/css
	# 
	# application/controllers
	# application/models
	# application/libraries
	# application/views
# 

local_repo = "~/Documents/github/prospero"
repo_name = "prospero"

echo "	Please input the commit message for github!: "

read commit_message

cp -r application/controller $local_repo/application/controller
