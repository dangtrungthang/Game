#include "Hub.h"
#include"Game.h"


void Hub::Update()
{
}

void Hub::Render()
{
	std::string output = "player 1:" + std::to_string(this->scorePlayer1)
		+ "    player 2:" + std::to_string(this->scorePlayer2);
	CGame::GetInstance()->DrawUIText(output, boundBox);
}

Hub::Hub()
{
}


Hub::~Hub()
{
}
