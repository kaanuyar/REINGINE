import random	


def step(dic):
	#print(dic)

	if dic["isGameOver"]:
		print("Game is over :)")

	return random.randint(0,360)