/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:12:02 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/18 19:55:29 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

std::string	get_next_option(std::string path)
{
	size_t last_slash_pos = path.rfind('/');
	if (last_slash_pos < path.size())
		return (path.substr(0, last_slash_pos));
	return (path);
}

int check_path(std::string path)
{
	struct stat	buf;
	if (stat(path.c_str(), &buf) != 0)
		return (0);
	if (S_ISDIR(buf.st_mode))
	{
		DIR* dir = opendir(path.c_str());
		if (!dir)
			return (-2);
		closedir(dir);
		return (2);
	}
	std::ifstream file(path);
	if (file.is_open())
		return (1);
	return (-1);
}

std::string	get_extension(std::string file_name)
{
	size_t dot_pos = file_name.find('.');
	return (file_name.substr(dot_pos, file_name.size()));
}

std::string	get_extension_type(std::string extension) {
	std::map<std::string, std::string> extension_list;
    extension_list[".aac"] = "audio/aac";
    extension_list[".abw"] = "application/x-abiword";
    extension_list[".arc"] = "application/x-freearc";
    extension_list[".avif"] = "image/avif";
    extension_list[".avi"] = "video/x-msvideo";
    extension_list[".azw"] = "application/vnd.amazon.ebook";
    extension_list[".bin"] = "application/octet-stream";
    extension_list[".bmp"] = "image/bmp";
    extension_list[".bz"] = "application/x-bzip";
    extension_list[".bz2"] = "application/x-bzip2";
    extension_list[".cda"] = "application/x-cdf";
    extension_list[".csh"] = "application/x-csh";
    extension_list[".css"] = "text/css";
    extension_list[".csv"] = "text/csv";
    extension_list[".doc"] = "application/msword";
    extension_list[".docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
    extension_list[".eot"] = "application/vnd.ms-fontobject";
    extension_list[".epub"] = "application/epub+zip";
    extension_list[".gz"] = "application/gzip";
    extension_list[".gif"] = "image/gif";
    extension_list[".html"] = "text/html";
    extension_list[".ico"] = "image/vnd.microsoft.icon";
    extension_list[".ics"] = "text/calendar";
    extension_list[".jar"] = "application/java-archive";
    extension_list[".jpeg"] = "image/jpeg";
    extension_list[".js"] = "text/javascript";
    extension_list[".json"] = "application/json";
    extension_list[".jsonld"] = "application/ld+json";
    extension_list[".mid"] = "audio/midi";
    extension_list[".midi"] = "audio/x-midi";
    extension_list[".mjs"] = "text/javascript";
    extension_list[".mp3"] = "audio/mpeg";
    extension_list[".mp4"] = "video/mp4";
    extension_list[".mpeg"] = "video/mpeg";
    extension_list[".mpkg"] = "application/vnd.apple.installer+xml";
    extension_list[".odp"] = "application/vnd.oasis.opendocument.presentation";
    extension_list[".ods"] = "application/vnd.oasis.opendocument.spreadsheet";
    extension_list[".odt"] = "application/vnd.oasis.opendocument.text";
    extension_list[".oga"] = "audio/ogg";
    extension_list[".ogv"] = "video/ogg";
    extension_list[".ogx"] = "application/ogg";
    extension_list[".opus"] = "audio/opus";
    extension_list[".otf"] = "font/otf";
    extension_list[".png"] = "image/png";
    extension_list[".pdf"] = "application/pdf";
    extension_list[".php"] = "application/x-httpd-php";
    extension_list[".ppt"] = "application/vnd.ms-powerpoint";
    extension_list[".pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
    extension_list[".rar"] = "application/vnd.rar";
    extension_list[".rtf"] = "application/rtf";
    extension_list[".sh"] = "application/x-sh";
    extension_list[".svg"] = "image/svg+xml";
    extension_list[".tar"] = "application/x-tar";
    extension_list[".tiff"] = "image/tiff";
    extension_list[".ts"] = "video/mp2t";
    extension_list[".ttf"] = "font/ttf";
    extension_list[".txt"] = "text/plain";
    extension_list[".vsd"] = "application/vnd.visio";
    extension_list[".wav"] = "audio/wav";
    extension_list[".weba"] = "audio/webm";
    extension_list[".webm"] = "video/webm";
    extension_list[".webp"] = "image/webp";
    extension_list[".woff"] = "font/woff";
    extension_list[".woff2"] = "font/woff2";
    extension_list[".xhtml"] = "application/xhtml+xml";
    extension_list[".xls"] = "application/vnd.ms-excel";
    extension_list[".xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
    extension_list[".xml"] = "application/xml";
    extension_list[".xul"] = "application/vnd.mozilla.xul+xml";
    extension_list[".zip"] = "application/zip";
    extension_list[".3gp"] = "video/3gpp";
    extension_list[".3g2"] = "video/3gpp2";
    extension_list[".7z"] = "application/x-7z-compressed";
    std::map<std::string, std::string>::iterator it = extension_list.find(extension);
    if (it != extension_list.end()) {
        return it->second;
    }
    return extension_list["application/octet-stream"];
}

std::string	get_date(void)
{
	time_t		ct = time(NULL);
	tm * 		curr_time;
	char		date[29];
	
	curr_time = localtime(&ct);
	strftime(date, 29, "%a, %d %b %G %R:%S GMT", curr_time);
	return (date);
}
