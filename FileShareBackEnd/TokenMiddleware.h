#ifndef TOKEN_MIDDLEWARE_H
#define TOKEN_MIDDLEWARE_H
#include <crow_all.h>
#include <CurrentUserManagement.h>

class TokenMiddleware {
public:

	struct context {

	};

	TokenMiddleware(CurrentUserManagement& sessionManagement);

	void before_handle(crow::request& request, crow::response& response, context& context);
	void after_handle(crow::request& req, crow::response& response, context& context);

private:

	CurrentUserManagement _sessionManagement;
};


#endif // TOKEN_MIDDLEWARE_H
