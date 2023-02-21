import socket
import threading
import sys 
import argparse
import time

#TODO: Implement all code for your server here

# Use sys.stdout.flush() after print statemtents

def acceptNewClient(conn, addr):
	data = conn.recv(1024).decode()

	passcode, username = data.split("\n")

	if passcode != args.passcode:
		conn.send(b"Incorrect passcode")
	else:
		conn.send(b"CONNECTED")
		msg = username + " joined the chatroom"
		print(msg)
		sys.stdout.flush()
		for client in clients:
			clients[client].sendto(msg.encode(), client)
		clients[addr] = conn
		usernames[addr] = username

		while True:
			data = conn.recv(1024).decode()
			if data == ":Exit":
				msg = usernames[addr] + " left the chatroom"
				print(msg)
				sys.stdout.flush()
				for client in clients:
					if client != addr:
						clients[client].sendto(msg.encode(), client)
				break
			else:
				if data == ":)":
					data = "[feeling happy]"
				elif data == ":(":
					data = "[feeling sad]"
				elif data == ":mytime":
					data = time.ctime()
				elif data == ":+1hr":
					data = time.ctime(time.time() + 3600)
				msg = usernames[addr] + ": " + data
				print(msg)
				sys.stdout.flush()
				for client in clients:
					if client != addr:
						clients[client].sendto(msg.encode(), client)

if __name__ == "__main__":
	host = "127.0.0.1"
	clients = {}
	usernames = {}

	parser = argparse.ArgumentParser()
	parser.add_argument("-start", "--start", action="store_true")
	parser.add_argument("-port", "--port", action="store_true")
	parser.add_argument("port", type=str)
	parser.add_argument("-passcode", "--passcode", action="store_true")
	parser.add_argument("passcode", type=str)

	args = parser.parse_args()
	if args.start:
		port = args.port

		sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		sock.bind(("", int(port)))
		sock.listen(1)

		print("Server started on port " + port + ". Accepting connections")
		sys.stdout.flush()

		while True:
			conn, addr = sock.accept()
			threading.Thread(target=acceptNewClient, args=(conn, addr)).start()

			"""
			while True:
				data = conn.recv(1024).decode()
				print(username + ": " + data)
				sys.stdout.flush()
			"""
				