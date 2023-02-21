import socket
import threading
import sys 
import argparse


#TODO: Implement a client that connects to your server to chat with other clients here

# Use sys.stdout.flush() after print statemtents

def join(args):
	if args.join:
		host = args.host
		port = args.port

		sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		sock.connect((host, port))
		sock.send(args.passcode.encode())
		sock.send(b"\n")
		sock.send(args.username.encode())

		connected = sock.recv(1024).decode()
		sys.stdout.flush()
		
		if connected == "Incorrect passcode":
			print(connected)
			sys.stdout.flush()
		elif connected == "CONNECTED":
			print("Connected to " + host + " on port " + str(port))
			sys.stdout.flush()

			threading.Thread(target=send, args=(sock,)).start()
			threading.Thread(target=receive, args=(sock,)).start()
		
		#sock.close()

def receive(sock):
	while True:
		try:
			data = sock.recv(1024).decode()	
			if data != "":	
				print(data)
				sys.stdout.flush()
		except:
			break

def send(sock):
	while True:
		msg = input()
		sock.send(msg.encode())
		if msg == ":Exit":
			break
	sock.close()

if __name__ == "__main__":
	parser = argparse.ArgumentParser()
	parser.add_argument("-join", "--join", action="store_true")
	parser.add_argument("-host", "--host", action="store_true")
	parser.add_argument("host", type=str)
	parser.add_argument("-port", "--port", action="store_true")
	parser.add_argument("port", type=int)
	parser.add_argument("-username", "--username", action="store_true")
	parser.add_argument("username", type=str)
	parser.add_argument("-passcode", "--passcode", action="store_true")
	parser.add_argument("passcode", type=str)

	args = parser.parse_args()

	threading.Thread(target=join, args=(args,)).start()