
#pragma warning(disable : 4996)

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <string.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include <map>
#include <vector>
using namespace std;
using namespace sf;

fstream openData;

sf::RenderWindow window(sf::VideoMode(900, 700), "SFML works!");

//* creeaza bilele

class Forme {

	sf::Texture texture;
	sf::CircleShape shape;
	int outline = 5;
	int x=0, y=0;
	int pozMingeShopX[6], pozMingeShopY[6];
 	int radius = 50;
public:
	//* bilele din magazin
	Forme()
	{
		int i, j,nr=0;
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 2; j++)
			{
				pozMingeShopX[nr] = 150 * j + 350;
				pozMingeShopY[nr]=  150 * i + 150 + i * 20;
				nr++;
			}
		}
	}
	int getMingeShopX(int nr)
	{
		return pozMingeShopX[nr];
	}
	int getMingeShopY(int nr)
	{
		return pozMingeShopY[nr];
	}
	void setPosition(int xC, int yC)
	{
		x = xC;
		y = yC;
	}
	int getPositionX()
	{
		return x;
	}
	int getPositionY()
	{
		return y;
	}
	void setTexture(string adresa)
	{
		texture.loadFromFile(adresa);
		texture.setSmooth(true);

	}
	void setRadius(int rad)
	{
		radius = rad;
	}
	int getRadius()
	{
		return radius;
	}
	void getInfo()
	{
		cout <<"Textura: " <<radius<<endl;
		cout << "Outline: " << outline << endl;
		cout << "Pozitie: " << x << " " << y << endl;
	}
	void setOutline(int out)
	{
		outline = out;
	}
	sf::CircleShape getNeutralBall()
	{  
		shape.setRadius(radius);
		shape.setTexture(&texture,true);
		//*shape.setTextureRect(sf::IntRect(150, 550, 650, 650));
		shape.setOutlineThickness(outline);
		shape.setOutlineColor(sf::Color(215, 218, 215));
		
		shape.setPosition(x, y);

		return shape;
	}
	sf::CircleShape getBall(bool state)
	{
		//*minge verde
		if (state == true)
		{   
			shape.setRadius(radius);
			shape.setTexture(&texture, true);
			//*shape.setTextureRect(sf::IntRect(150, 550, 650, 650));
			shape.setOutlineThickness(outline);
			shape.setOutlineColor(sf::Color(30, 251, 0));
			shape.setPosition(x, y);
			return shape;
		}
		if (state == false)
		{
			shape.setRadius(radius);
			shape.setTexture(&texture, true);
			//*shape.setTextureRect(sf::IntRect(150, 550, 650, 650));
			shape.setOutlineThickness(outline);
			shape.setOutlineColor(sf::Color(251, 44, 0));
			shape.setPosition(x, y);
			return shape;

		}
	}
	sf::CircleShape getShopLockedBall()
	{
		shape.setRadius(radius);
		shape.setTexture(&texture, true);
		shape.setOutlineThickness(outline);
		shape.setOutlineColor(sf::Color(255, 0, 0));
		shape.setPosition(x, y);
		return shape;
	}

	sf::CircleShape getShopUnlockedBall()
	{
		shape.setRadius(radius);
		shape.setTexture(&texture, true);
		shape.setOutlineThickness(outline);
		shape.setOutlineColor(sf::Color(70, 255, 3));
		shape.setPosition(x, y);
		return shape;
	}
	sf::CircleShape getShopChoiceBall()
	{
		shape.setRadius(radius);
		shape.setTexture(&texture, true);
		shape.setOutlineThickness(outline);
		shape.setOutlineColor(sf::Color(255, 3, 222));
		shape.setPosition(x, y);
		return shape;

	}
};


void drawCerc(CircleShape cerc)
{
	window.draw(cerc);
}

//* seteaza dificultatea

class Dificultate {
	int speed;
	string dificultate;
	bool alegere=false;
public:
	Dificultate()
	{  //* se seteaza automat pe medium dificultatea
		dificultate = "medium";
		speed = 2;
	}
	Dificultate(string dificultateC)
	{
		dificultate = dificultateC;
		if (dificultate == "easy")
		{
			speed = 3;
			
		}
		else if (dificultate == "medium")
		{
			speed = 2;
	
		}
		else  if (dificultate == "hard")
		{
			speed = 1;
		 
		}
		 else {
			cout << "Ati introdus dificultatea gresita ! Se va pune automat medium" << endl;
			speed = 2;
		}
	}
	void setDif(string dificultateC)
	{
		dificultate=dificultateC;
		if (dificultate == "easy")
		{
			speed = 3;
	
		}
		else if (dificultate == "medium")
		{
			speed = 2;
			
		}
		else  if (dificultate == "hard")
		{
			speed = 1;
			
		}
	}
	void afisare()
	{
		cout << "Speed: " << speed << endl;
		cout <<"Dificultate: "<< dificultate;
	}
	void setSpeed(int sp)
	{
		speed = sp;
	}
	int getSpeed()
	{
		return speed;
	}
	string getDif()
	{
		return dificultate;
	}
	bool getState()
	{
		return alegere;
	}
	void setState(bool state)
	{
		alegere = state;
	}
};

//* manipuleaza fisierele

class Shop {
	int coins=0;
public:

	void updateCoins()
	{
	
		openData.open("Shop.txt", fstream::in);
		openData>> coins;
		openData.close();
	}
	void saveCoins()
	{
		openData.open("Shop.txt", fstream::out);
		openData << coins;
		openData.close();
	}
	int getCoins()
	{
		return coins;
	}
	void addCoins(string dificultateC)
	{
		if (dificultateC =="easy")
			coins = coins + 1;
		else if (dificultateC== "medium")
			coins = coins + 3;
		else if (dificultateC=="hard")
			coins = coins + 5;
	}
	void removeCoins(int nr)
	{
		coins = coins - nr;
	}
};

//* creeaza sprite-urile

class Texturi_Shop {
	sf::Texture TRaft;
	sf::Sprite SRaft;
	sf::Texture TDraperii;
	sf::Sprite SDraperii;
	sf::Texture TRoom;
	sf::Sprite SRoom;
	sf::Texture TpriceT;
	sf::Sprite SpriceT;
	sf::Texture TStea;
	sf::Sprite SStea;
	sf::Texture TYes;
	sf::Sprite SYes;
	sf::Sprite SNo;
	sf::Texture TNo;
public:
	Texturi_Shop()
	{
		TYes.loadFromFile("yes.png");
		TYes.setSmooth(true);
		SYes.setTexture(TYes);
		SYes.setScale(0.25f, 0.25f);
		SYes.setPosition(200, 300);

		TNo.loadFromFile("no.png");
		TNo.setSmooth(true);
		SNo.setTexture(TNo);
		SNo.setScale(0.25f, 0.25f);
		SNo.setPosition(600, 300);


		TpriceT.loadFromFile("skinuri\\priceT.png");
		TpriceT.setSmooth(true);
		SpriceT.setTexture(TpriceT);
		SpriceT.setScale(0.075f, 0.075f);

		TRaft.loadFromFile("raft.png");
		TRaft.setSmooth(true);
		SRaft.setTexture(TRaft);
		SRaft.setPosition(260, 50);
		SRaft.setScale(1.2f, 1.3f);

		TDraperii.loadFromFile("draperii.png");
		TDraperii.setSmooth(true);
		SDraperii.setTexture(TDraperii);
		SDraperii.setScale(1.2f, 1.3f);;

		TRoom.loadFromFile("room.jpg");
		TRoom.setSmooth(true);
		SRoom.setTexture(TRoom);

		TStea.loadFromFile("stea.png");
		TStea.setSmooth(true);
		SStea.setTexture(TStea);
		SStea.setScale(0.1f, 0.1f);

	}
	Sprite getRoomSprite()
	{
		return SRoom;
	}
	Sprite getRaftSprite()
	{

		return SRaft;
	}
	Sprite getDraperiiSprite()
	{

		return SDraperii;
	}
	Sprite getSteaSprite()
	{
		return SStea;
	}
	Sprite getPriceSprite(int x,int y)
	{
		SpriceT.setPosition(x, y);
		return SpriceT;
	}
	void setPositionStea(int x,int y,float i)
	{
		SStea.setColor(sf::Color(int(i)%155+100, int(i) % 255, 180));

		SStea.setPosition(cos(i * 3.14159265 / 180.0) * (-250) - sin(i * 3.14159265 / 180.0) * (300) +x ,
			              sin(i * 3.14159265 / 180.0) * (-250) + cos(i * 3.14159265 / 180.0) * (300) +y);
		
		
	}
	Sprite getYes()
	{
		return SYes;
	}
	Sprite getNo()
	{
		return SNo;
	}



};

//*se ocupa cu scrisul de pe ecran

class Scris {
	Text text;
	int pozX, pozY;
	string scris;
	public:
	Scris(sf::Font &fontulet,string s,int size,int x,int y,bool cul)
	{
		text.setFont(fontulet);
		scris = s;
		text.setString(scris);
		pozX = x;
		pozY = y;
		text.setCharacterSize(size);
		text.setPosition(x, y);
		if(cul==true)
		text.setFillColor(sf::Color::Green);
	}
	void afisare()
	{
		window.draw(text);
	}
	int getX()
	{
		return pozX;
	}
	int getY()
	{
		return pozY;
	}
	void afisarePozitii()
	{
		cout << "X: " << pozX<<endl;
		cout << "Y: " << pozY << endl;
	}
	void setFont(sf::Font &fontulet)
	{
		text.setFont(fontulet);
	}
	void setScris(string s)
	{
		scris = s;
		text.setString(scris);
	}
	void setPozitii(int x, int y)
	{
		pozX = x;
		pozY = y;
	}
	Text getText()
	{
		return text;
	}


};

//* retine nr de skinuri,skinul actual etc.

class Skins {
	int nrSkinuri=0;
	vector<string> numeSkinuri;
	map<std::string, int> texturaCurenta;
public:
	Skins()
	{
		string x;
		string A;
		ifstream f("skinuri\\skins.txt");
		ifstream g("skinuri\\unlockedSkins.txt");
		while (getline(f,x))
		{
			
			numeSkinuri.push_back(x);
			getline(g, A);
			if (A == "0")
			{
				texturaCurenta[x] = 0;
			}
			if (A == "1")
			{
				texturaCurenta[x] = 1;
			}
			if (A == "2")
			{
				texturaCurenta[x] = 2;
			}
			nrSkinuri++;  
		}
	}
	void afisareAdrese()
	{
		int i;
		for (i = 0; i < nrSkinuri; i++)
		cout << numeSkinuri[i] << endl;
	}
	string resumeSkin()
	{
		int i;
		for (i = 0; i < nrSkinuri; i++)
		{
			if (texturaCurenta[numeSkinuri[i]] == 2)
				return numeSkinuri[i];
		}
		return "";
	}
	string getPozaString(int i)
	{ 
		//*cout<< "skinuri\\" + numeSkinuri[i]<<endl;
		return "skinuri\\"+numeSkinuri[i];
	}
	void resetChoiceTexture()
	{
		int i;
		for (i = 0; i < nrSkinuri; i++)
			if (texturaCurenta[numeSkinuri[i]] == 2)
				texturaCurenta[numeSkinuri[i]] = 1;
	}
	void setState(int state, int nr)
	{
		texturaCurenta[numeSkinuri[nr]] = state;
	}
	int getState(int nr)
	{
		return texturaCurenta[numeSkinuri[nr]];
	}
	int getNrSkinuri()
	{
		return nrSkinuri;
	}
	void saveUnlockedSkins()
	{
		int i;
		openData.open("skinuri\\unlockedSkins.txt", fstream::out);
		for (i = 0; i < nrSkinuri; i++)
		{
			openData << texturaCurenta[numeSkinuri[i]] << endl;

		}
		openData.close();
	}
};

//* clasa de muzica

class Muzica {
	sf::SoundBuffer buffer;
	sf::Sound soundNo;
	sf::Music musicPlay;
public:
	Muzica()
	{
		buffer.loadFromFile("sounds\\no.wav");
		soundNo.setBuffer(buffer);
		musicPlay.openFromFile("sounds\\muzica joc.wav");
	}

	Sound getNoSound()
	{

		return soundNo;
	}
	void playSoundNo()
	{
	soundNo.play();
	}
	void playMusicGame()
	{
		musicPlay.play();
	}
	void stopMusic()
	{
		musicPlay.stop();
	}

};


Muzica Muzicuta;
Shop shop;
Forme minge;
Dificultate dif;
Texturi_Shop texturi_shop;
Skins skins;
float i = 0.01f;
string SKIN_ALES;

//* meniul

int ButoaneMeniuPrincipal(Scris PlayGreen,Scris Play,Scris Magazin, Scris MagazinGreen,Scris Save_Game_Green,Scris Saved,Scris Save_Game)
{
	sf::Vector2i position = sf::Mouse::getPosition(window);

	//*sa se roteasca steluta
	i++;
	if (i > 40000)
	{
		i = 0;
		
	}
	texturi_shop.setPositionStea(position.x, position.y,i);

	window.draw(texturi_shop.getSteaSprite());

	if (position.x >= 370 && position.x <= 465 && position.y >= 130 && position.y <= 185)
	{
		PlayGreen.afisare();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return 1;
		}
	}
	else { Play.afisare(); }

	if (position.x >= 370 && position.x <= 485 && position.y >= 280 && position.y <= 345)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return 2;
		}
		MagazinGreen.afisare();
	}
	else { Magazin.afisare(); }


	if (position.x >= 325 && position.x <= 540 && position.y >= 430 && position.y <= 490)
	{
		Save_Game_Green.afisare();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			shop.saveCoins();
			window.clear();
			Saved.afisare();
			window.display();

			sf::Time t1 = sf::seconds(1);
			sf::sleep(t1);
		}

	}
	else { Save_Game.afisare(); }

	return 0;
}

//* butoanele de dificultate

void ButoaneDificultate(Scris EasyGreen,Scris Easy, Scris Medium,Scris Hard,Scris MediumGreen,Scris HardGreen)
{
	window.clear();
	sf::Vector2i position = sf::Mouse::getPosition(window);
	EasyGreen.afisare();
	Medium.afisare();
	Hard.afisare();

	if (position.x >= 180 && position.x <= 285 && position.y >= 320 and position.y <= 380)
	{
		EasyGreen.afisare();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			dif.setDif("easy");
			dif.setState(true);
		}

	}
	else { Easy.afisare(); }

	if (position.x >= 350 && position.x <= 522 && position.y >= 320 and position.y <= 380)
	{
		MediumGreen.afisare();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			dif.setDif("medium");
			dif.setState(true);
		}

	}
	else { Medium.afisare(); }


	if (position.x >= 590 && position.x <= 705 && position.y >= 320 and position.y <= 380)
	{
		HardGreen.afisare();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			dif.setDif("hard");
			dif.setState(true);
		}

	}
	else { Hard.afisare(); }



}

//* jocul in sine

void StartJoc(Scris textScore, Scris textScoreNr,Clock &clock,Time timpul)
{

	sf::Vector2i position = sf::Mouse::getPosition(window);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (position.x <= minge.getPositionX() + minge.getRadius() * 2 && position.x >= minge.getPositionX())
		{
			if (position.y >= minge.getPositionY() && position.y <= minge.getPositionY() + minge.getRadius() * 2)
			{
				window.clear();

				textScore.afisare();
				textScoreNr.setScris(to_string(shop.getCoins()));
				textScoreNr.afisare();

				timpul = clock.getElapsedTime();

				if (timpul.asSeconds()<= dif.getSpeed())
				{
					drawCerc(minge.getBall(true));
					shop.addCoins(dif.getDif());
				}
				else { drawCerc(minge.getBall(false)); }

				window.display();

				sf::Time t1 = sf::seconds(0.2f);
				sf::sleep(t1);

				clock.restart();

				minge.setPosition(rand() % 800, rand() % 600);

			}
		}
	}

	drawCerc(minge.getNeutralBall());

	
}
bool stateShop;


void mutareCursor(int x, int y)
{
	if (stateShop == false)
	{
		sf::Vector2i poz(x, y);
		sf::Mouse::setPosition(poz, window);
		stateShop = true;
	}

}

//* afiseaza shop-ul

int OpenShop(Font font,Scris textScoreShop, Scris textScoreNrShop)
{
	window.clear();
	window.draw(texturi_shop.getRoomSprite());
	window.draw(texturi_shop.getRaftSprite());
	window.draw(texturi_shop.getDraperiiSprite());

	textScoreShop.afisare();
	textScoreNrShop.setScris(to_string(shop.getCoins()));
	textScoreNrShop.afisare();

	//*sa evit un bug,mut cursorul mai in stanga
	mutareCursor(380, 300);

	int nr = 0, y = 5,i,j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 2; j++)
		{
			minge.setTexture(skins.getPozaString(nr));
			minge.setPosition(150 * j + 350, 150 * i + 150 + i * 20);
			if (skins.getState(nr) == 0)
			{
				window.draw(minge.getShopLockedBall());
			}
			else if (skins.getState(nr) == 1)
				window.draw(minge.getShopUnlockedBall());
			else if (skins.getState(nr) == 2)
				window.draw(minge.getShopChoiceBall());

			window.draw(texturi_shop.getPriceSprite(150 * j + 355, 150 * i + 235 + i * 20));
			Scris Pret(font, to_string(400 * (nr + 1)), 30, 150 * j + 374 + y, 150 * i + 260 + i * 20, false);
			Pret.afisare();
			nr++;
		}
		y = 0;
	}
	sf::Vector2i position = sf::Mouse::getPosition(window);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		for (i = 0; i < skins.getNrSkinuri(); i++)
			if (position.x <= minge.getMingeShopX(i) + minge.getRadius() * 2 && position.x >= minge.getMingeShopX(i))
			{
				if (position.y >= minge.getMingeShopY(i) && position.y <= minge.getMingeShopY(i) + minge.getRadius() * 2)
				{
					return i;

				}

			}
	}
	return -1;
}

int main()
{
	
	window.setFramerateLimit(60);
	shop.updateCoins();
	srand(time(0));
	minge.setTexture("skinuri\\default.png");
	minge.setPosition(rand()%850, rand()%650);



	sf::Clock clock;
	sf::Time timpul;
	sf::Font font;

	font.loadFromFile("font.otf");

	Scris textScore(font,"Coins:",24,770,15,false);
	Scris textScoreNr(font, to_string(shop.getCoins()), 24, 840, 15, false);
	Scris textScoreShop(font, "Coins:", 50, 20, 550, false);
	Scris textScoreNrShop(font, to_string(shop.getCoins())+"$", 50, 160, 550, false);
    Scris Play(font, "Play", 55, 370, 130, false);
	Scris PlayGreen(font, "Play", 55, 370, 130, true);
	Scris Magazin(font, "Shop", 55, 370, 280, false);
	Scris MagazinGreen(font, "Shop", 55, 370, 280, true);
	Scris Save_Game(font, "Save game", 55, 325, 430, false);
	Scris Save_Game_Green(font, "Save game", 55, 325, 430, true);
	Scris Saved(font,"The game is saved!", 55, 260, 300,false);
	Scris Easy(font, "Easy", 55, 190, 320, false);
	Scris EasyGreen(font, "Easy", 55, 190, 320, true);
	Scris Medium(font, "Medium", 55, 360, 320, false);
	Scris MediumGreen(font, "Medium", 55, 360, 320, true);
	Scris Hard(font, "Hard", 55, 600, 320, false);
	Scris HardGreen(font, "Hard", 55, 600, 320, true);

	int menu = 0,j,i,var;
    
	while (window.isOpen())
	{
	
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				shop.saveCoins();
				window.close();
			}
		}

		window.clear();

		if (menu == 0)
		{
			textScore.afisare();
			textScoreNr.setScris(to_string(shop.getCoins()));
			textScoreNr.afisare();

			//*butoanele de menu
			menu = ButoaneMeniuPrincipal(PlayGreen, Play, Magazin, MagazinGreen, Save_Game_Green, Saved, Save_Game);  
			//*daca s-a apasat play va returna 1 pentru a alege dificultatea
		}

		if (menu == 1)
		{
			window.clear();
			textScore.afisare();
			textScoreNr.setScris(to_string(shop.getCoins()));
			textScoreNr.afisare();

			//*verifica ce skin a fost ales de player ultima data
			if (skins.resumeSkin() != "")
				SKIN_ALES = "skinuri\\" + skins.resumeSkin();
			else { 
				SKIN_ALES = "skinuri\\default.png";
			}
			//* dificultatea o fu aleasa si se poate juca
			if (dif.getState() == true)
			{  
				if(SKIN_ALES!="")
				minge.setTexture(SKIN_ALES);
				
				//*we don't talk about this
				if (dif.getDif() == "easy")minge.setRadius(50);if (dif.getDif() == "medium")minge.setRadius(40);if (dif.getDif() == "hard")minge.setRadius(30);

				StartJoc(textScore, textScoreNr,clock,timpul);
		    }
			//* dificultatea nu a fost inca aleasa, se alege acum
			if (dif.getState() == false)
			{
				Muzicuta.playMusicGame();
				ButoaneDificultate(EasyGreen,Easy,Medium,Hard, MediumGreen,HardGreen);
			}

	}
		//* intefata shop + verifica daca apas sa cumpar
		if (menu == 2)
		{
			window.clear();
			var = -1;
			var = OpenShop(font, textScoreShop, textScoreNrShop);
			if (var != -1)
			{
				if (shop.getCoins() >= (400 * (var + 1)) && skins.getState(var)==0) 
				{
					menu = 3;
					stateShop = false;
				}
				else if (skins.getState(var) == 1)
				{
					skins.resetChoiceTexture();
					skins.setState(2, var);
					SKIN_ALES=skins.getPozaString(var);
					skins.saveUnlockedSkins();
				}
				else if(shop.getCoins() < (400 * (var + 1)) && skins.getState(var) == 0)
				{ 
			
					Muzicuta.playSoundNo();

				}


				//*sa aleaga skin-ul
			}
		}
           //*sa aleg daca sa cumpar sau nu skin-ul ales
		if (menu == 3)
		{
			Scris confirmarePret(font, "Do you want to buy the " + to_string(400 * (var + 1))+" skin?",55, 100, 100, false);
			confirmarePret.afisare();
			window.draw(texturi_shop.getYes());
			window.draw(texturi_shop.getNo());

			if (stateShop == false)
			{
				mutareCursor(450, 250);
				stateShop = true;
			}
			sf::Vector2i position = sf::Mouse::getPosition(window);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				//*yes
				if (position.x >= 196 && position.x <= 347 && position.y >= 294 && position.y <= 440)
				{
					skins.setState(true, var);
					shop.removeCoins(400 * (var + 1));
					shop.saveCoins();
					skins.saveUnlockedSkins();
					menu = 2;
					stateShop = false;
				}
				//*no
				if (position.x >= 592 && position.x <= 748 && position.y >= 294 && position.y <= 440)
				{
					menu = 2;
					stateShop = false;
				}
			}

		}
		//* daca se apasa esc,se intoarce la meniul principal
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			shop.saveCoins();
			menu = 0;
			stateShop = false;
			dif.setState(false);
			Muzicuta.stopMusic();
		}
		window.display();
	}
	
	return 0;

}

