compile:
	gcc -Wall main.c -o serveme

restart: compile
	systemctl restart --now short.service

stop:
	systemctl stop short.service

status:
	systemctl status short.service

install-systemd: compile
	install systemd/short.service /etc/systemd/system/	
	systemctl daemon-reload

run: compile
	./serveme 
