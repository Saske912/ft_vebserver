server {
	host 127.0.0.1										# host address
	port 1024									# port to listen
	server_names hostname.local hostname.test			# server names
	#error_page 404 error_404.html						# error page for 404
	#error_page 401 error_401.html						# error page for 401
	client_max_body_size 100M							# limit client max body size
	route / {							    # route for file $(index)/public/index.html
	    cgi_extension php php				# cgi file for specified extension
		allowed_methods GET POST				# allowed methods for route
		root content/GeoCin
		index index.php
	}
};
