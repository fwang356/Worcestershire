import socket
import threading
import sys 
import argparse
import time

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

def startGame(conn, addr):
	while True:
		guess = conn.recv(1024).decode()
		result = checkGuess(word, guess)

		if result == "invalid":
			result = "Please enter a valid word."
		
		conn.send(result.encode())
			

def checkGuess(word, guess):
	result = ""
	if guess not in guesses:
		result = "invalid"
	else:
		for i in range(5):
			if word[i] == guess[i]:
				result += "G"
			elif guess[i] in word:
				result += "Y"
			else:
				result += "R"
	return result

if __name__ == "__main__":
	host = "127.0.0.1"
	word = "apple"
	guesses = ["apple", "happy"]
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
			threading.Thread(target=startGame, args=(conn, addr)).start()

			"""
			while True:
				data = conn.recv(1024).decode()
				print(username + ": " + data)
				sys.stdout.flush()
			"""
				