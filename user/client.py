#!/usr/bin/env python

import socket
import sys

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_address = ('localhost', 8080)
sock.connect(server_address)

message = 'GET /../webserv.c HTTP/1.1\n\n'
sock.sendall(message)

while True:
	data = sock.recv(1000)
	if data != "":
		print data
	else:
		break

sock.close()
