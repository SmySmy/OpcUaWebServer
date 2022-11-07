/*
   Copyright 2015 Kai Huebl (kai@huebl-sgh.de)

   Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
   Datei nur in Übereinstimmung mit der Lizenz erlaubt.
   Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

   Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
   erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
   GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

   Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
   im Rahmen der Lizenz finden Sie in der Lizenz.

   Autor: Kai Huebl (kai@huebl-sgh.de)

 */

#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include "OpcUaStackCore/Base/Log.h"
#include "OpcUaWebServer/WebServer/HttpContent.h"

using namespace OpcUaStackCore;

namespace OpcUaWebServer
{

	HttpContent::HttpContent(void)
	: HttpServerIf()
	, httpConfig_(NULL)
	{
	}

	HttpContent::~HttpContent(void)
	{
	}

	void
	HttpContent::httpConfig(HttpConfig* httpConfig)
	{
		httpConfig_ = httpConfig;
	}

	bool
	HttpContent::startup(void)
	{
		return true;
	}

	bool
	HttpContent::shutdown(void)
	{
		return true;
	}

	bool
	HttpContent::checkPath(const std::string& path)
	{
		// The directory must be within the archive

		uint32_t dep = 0;
		boost::filesystem::path::iterator it;
		boost::filesystem::path p(path);

		for (it = p.begin(); it != p.end(); it++) {
			std::stringstream ss;
			ss << *it;
			std::string directory = ss.str();

			if (directory == "/") continue;
			if (directory == "..") {
				if (dep == 0) return false;
				return false;
			}
			else {
				dep++;
			}


			std::cout << (*it).c_str() << std::endl;
		}

		return true;
	}

	void
	HttpContent::request(HttpRequest& httpRequest, HttpResponse& httpResponse)
	{
		std::string path = httpRequest.path();
		if (path == "/") {
			path = "/index.html";
		}
		else {
			if (!checkPath(path)) {
				httpResponse.statusCode(404);
				httpResponse.statusString("Not Found");
				return;
			}
		}

		std::string file = httpConfig_->webDirectory() + path;

		Log(Debug, "WebServer handle request")
		    .parameter("Method",  httpRequest.method())
		    .parameter("Path", httpRequest.path())
		    .parameter("File", file);

		// check if file exist
		if (!boost::filesystem::exists(file)) {
		    Log(Error, "cannot find file (404)!")
                .parameter("Method",  httpRequest.method())
                .parameter("Path", httpRequest.path())
                .parameter("File", file);
			httpResponse.statusCode(404);
			httpResponse.statusString("Not Found");
			return;
		}

		// read file
		boost::filesystem::ifstream ifs;
		ifs.open(file, std::ios::binary | std::ios::in);
		if (!ifs) {
            Log(Error, "cannot read file (404)!")
                .parameter("Method",  httpRequest.method())
                .parameter("Path", httpRequest.path())
                .parameter("File", file);
		    httpResponse.statusCode(404);
		    httpResponse.statusString("Not Found");
		    return;
		}

		std::stringstream ss;
		ss << ifs.rdbuf();

		// set content
		httpResponse.content(ss.str());
	}
}
