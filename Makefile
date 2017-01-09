
default:	build

clean:
	rm -rf Makefile objs

build:
	$(MAKE) -f objs/Makefile
	$(MAKE) -f objs/Makefile manpage

install:
	$(MAKE) -f objs/Makefile install

upgrade:
	/var/www/dream/nginx-pull-record//sbin/nginx -t

	kill -USR2 `cat /var/www/dream/nginx-pull-record//logs/nginx.pid`
	sleep 1
	test -f /var/www/dream/nginx-pull-record//logs/nginx.pid.oldbin

	kill -QUIT `cat /var/www/dream/nginx-pull-record//logs/nginx.pid.oldbin`
