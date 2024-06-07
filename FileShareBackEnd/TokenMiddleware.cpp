#include <TokenMiddleware.h>
#include <crow_all.h>
#include <CurrentUserManagement.h>

TokenMiddleware::TokenMiddleware(CurrentUserManagement& sessionManagement) {
	_sessionManagement = sessionManagement;
}

void TokenMiddleware::before_handle(crow::request& request, crow::response& response, context& context) {

	if (request.url != "/") {
		std::string sessionToken = request.get_header_value("Authorization");

		if (!_sessionManagement.ValidToken(sessionToken)) {
			response.code = 303;
			response.add_header("Location", "/login/failed");

		}
	}
	
}

void TokenMiddleware::after_handle(crow::request& request, crow::response& response, context& context) {

}
