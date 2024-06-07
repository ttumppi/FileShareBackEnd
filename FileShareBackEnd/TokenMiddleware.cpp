#include <TokenMiddleware.h>
#include <crow_all.h>
#include <CurrentUserManagement.h>
#include <list>
#include <algorithm>

TokenMiddleware::TokenMiddleware(CurrentUserManagement& sessionManagement, const std::list<std::string>& authenticatedUrls ) : _sessionManagement(sessionManagement) {
	_authenticatedUrls = authenticatedUrls;
	
}

void TokenMiddleware::before_handle(crow::request& request, crow::response& response, context& context) {

	if (request.url == "/") {
		std::string sessionToken = request.get_header_value("Cookie");

		if (_sessionManagement.ValidToken(sessionToken)) {
			response.code = 303;
			response.add_header("Location", "/homepage");
			response.end();
		}
	}
	if (UrlNeedsAuthentication(request.url)) {
		std::string sessionToken = request.get_header_value("Cookie");

		if (!_sessionManagement.ValidToken(sessionToken)) {
			response.code = 303;
			response.add_header("Location", "/login/failed");
			response.end();
		}
		
	}
	
}

void TokenMiddleware::after_handle(crow::request& request, crow::response& response, context& context) {

}

bool TokenMiddleware::UrlNeedsAuthentication(std::string& url) {

	return std::find(_authenticatedUrls.begin(), _authenticatedUrls.end(), url) != _authenticatedUrls.end();

}
