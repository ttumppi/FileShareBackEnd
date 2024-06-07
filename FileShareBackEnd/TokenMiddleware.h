#ifndef TOKEN_MIDDLEWARE_H
#define TOKEN_MIDDLEWARE_H
#include <crow_all.h>
#include <CurrentUserManagement.h>
#include <list>

class TokenMiddleware {
public:

	struct context {

	};

	TokenMiddleware(CurrentUserManagement& sessionManagement, const std::list<std::string>& authenticatedUrls);

	void before_handle(crow::request& request, crow::response& response, context& context);
	void after_handle(crow::request& req, crow::response& response, context& context);

private:

	bool UrlNeedsAuthentication(std::string& url);

	CurrentUserManagement& _sessionManagement;
	std::list<std::string> _authenticatedUrls;
};


#endif // TOKEN_MIDDLEWARE_H
