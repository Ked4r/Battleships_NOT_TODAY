
#include <iostream>
#include <windows.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <list>
#include <iterator>
#include <stdbool.h>
#include <chrono>

//rozdzielczość okna 
#define restx 1280
#define resty 1024

using namespace std;

//klasy przechowujace dane o statkach (p to poczatek , s to srodek , k to koniec. Te zmienne trzechowuja informacje o pozycji statku)
// stan to stan punktu statku 1 - poczatek czyli p . 2 - srodek czyli s lub koniec w zaleznosci od statku. 
class statek1
{
public:
	int p[2];
	int stan;
};

class statek2
{
public:
	int p[2];
	int k[2];
	int stan[2];
};

class statek3
{
public:
	int p[2];
	int s[2];
	int k[2];
	int stan[3];
};

class statek4
{
public:
	int p[2];
	int s[2];
	int s1[2];
	int k[2];
	int stan[4];
};

//Funckja losująca statki komputera
void wypelnienie_pc(statek1& s1, statek2& s2, statek3& s3, statek4& s4)
{
	srand(time(0));
	bool pentla = true;
	int i, j;

	//losowanie pozycji satku 1
	s1.p[0] = rand() % 6;
	s1.p[1] = rand() % 6;
	s1.stan = 1;

	//losowanie pozycji satku 2
	while (pentla)
	{
		s2.p[0] = rand() % 6;
		s2.p[1] = rand() % 6;
		
		if (i = rand() % 4)
		{
			if (i == 0)
			{
				s2.k[0] = s2.p[0] - 1;
				s2.k[1] = s2.p[1];
			}
			if (i == 1)
			{
				s2.k[0] = s2.p[0];
				s2.k[1] = s2.p[1] - 1;
			}
			if (i == 2)
			{
				s2.k[0] = s2.p[0] + 1;
				s2.k[1] = s2.p[1];
			}
			if (i == 3)
			{
				s2.k[0] = s2.p[0];
				s2.k[1] = s2.p[1] + 1;
			}
		}
		//zabezpieczenia przy losowaniu
		pentla = false;
		if ((s2.p[0] == s1.p[0]) && (s2.p[1] == s1.p[1]))
		{
			pentla = true;
		}
		if ((s2.k[0] == s1.p[0]) && (s2.k[1] == s1.p[1]))
		{
			pentla = true;
		}
		if ((s2.p[0] < 0) || (s2.p[1] >6))
		{
			pentla = true;
		}
		if ((s2.k[0] < 0) || (s2.k[1] > 6))
		{
			pentla = true;
		}
	}

	pentla = true;
	//losowanie pozycji satku 3
	while (pentla)
	{
		s3.p[0] = rand() % 7;
		s3.p[1] = rand() % 7;
		if (i = rand() % 4)
		{
			if (i == 0)
			{
				s3.k[0] = s3.p[0] - 2;
				s3.k[1] = s3.p[1];
			}
			if (i == 1)
			{
				s3.k[0] = s3.p[0];
				s3.k[1] = s3.p[1] - 2;
			}
			if (i == 2)
			{
				s3.k[0] = s3.p[0] + 2;
				s3.k[1] = s3.p[1];
			}
			if (i == 3)
			{
				s3.k[0] = s3.p[0];
				s3.k[1] = s3.p[1] + 2;
			}
		}
		//obliczanie srodkowego punktu statku na podstawie poczatkowego punktu i konczowego
		if (s3.p[0] == s3.k[0])
		{
			s3.s[0] = s3.p[0];
			s3.s[1] = (s3.p[1] + s3.k[1]) / 2;
			s3.stan[1] = 1;
		}
		else
		{
			s3.s[1] = s3.p[1];
			s3.s[0] = (s3.p[0] + s3.k[0]) / 2;
			s3.stan[1] = 1;
		}
		//zabezpieczenia przy losowaniu

		pentla = false;
		if ((s3.s[0] == s1.p[0]) && (s3.s[1] == s1.p[1]))
		{
			pentla = true;
		}
		if ((s3.s[0] == s2.p[0]) && (s3.s[1] == s2.p[1]))
		{
			pentla = true;
		}
		if ((s3.s[0] == s2.k[0]) && (s3.s[1] == s2.k[1]))
		{
			pentla = true;
		}
		if ((s3.k[1] == s1.p[1]) && (s3.k[0] == s1.p[0]))
		{
			pentla = true;
		}
		if ((s3.k[1] == s2.p[1]) && (s3.k[0] == s2.p[0]))
		{
			pentla = true;
		}
		if ((s3.k[1] == s2.k[1]) && (s3.k[0] == s2.k[0]))
		{
			pentla = true;
		}
		if ((s3.k[1] == s3.p[1]) && (s3.k[1] == s3.p[0]))
		{
			pentla = true;
		}
		if ((s3.p[0] == s1.p[0]) && (s3.s[1] == s1.p[1]))
		{
			pentla = true;
		}
		if ((s3.p[0] == s2.p[0]) && (s3.s[1] == s2.p[1]))
		{
			pentla = true;
		}
		if ((s3.p[0] == s2.k[0]) && (s3.s[1] == s2.k[1]))
		{
			pentla = true;
		}
		if ((s3.k[1] < 0) || (s3.k[1] > 6))
		{
			pentla = true;
		}
		if ((s3.k[0] < 0) || (s3.k[0] > 6))
		{
			pentla = true;
		}

	}

	pentla = true;
	//losowanie pozycji satku 4
	while (pentla)
	{
		s4.p[0] = rand() % 7;
		s4.p[1] = rand() % 7;
		if (i = rand() % 4)
		{
			if (i == 0)
			{
				s4.k[0] = s4.p[0] - 3;
				s4.k[1] = s4.p[1];
			}
			if (i == 1)
			{
				s4.k[0] = s4.p[0];
				s4.k[1] = s4.p[1] - 3;
			}
			if (i == 2)
			{
				s4.k[0] = s4.p[0] + 3;
				s4.k[1] = s4.p[1];
			}
			if (i == 3)
			{
				s4.k[0] = s4.p[0];
				s4.k[1] = s4.p[1] + 3;
			}
		}
		//obliczanie srodkowych puktow na podstawie poczatkowego i koncowego
		if (s4.p[0] == s4.k[0])
		{
			s4.s[0] = s4.p[0];
			s4.s1[0] = s4.p[0];

			if (s4.p[1] > s4.k[1])
			{
				s4.s[1] = s4.p[1] - 1;
				s4.s1[1] = s4.p[1] - 2;
				s4.stan[2] = 1;
				s4.stan[3] = 1;
			}
			else
			{
				s4.s[1] = s4.p[1] + 1;
				s4.s1[1] = s4.p[1] + 2;
				s4.stan[2] = 1;
				s4.stan[3] = 1;
			}
		}
		else
		{
			s4.s[1] = s4.p[1];
			s4.s1[1] = s4.p[1];
			if (s4.p[0] > s4.k[0])
			{
				s4.s[0] = s4.p[0] - 1;
				s4.s1[0] = s4.p[0] - 2;
				s4.stan[2] = 1;
				s4.stan[3] = 1;
			}
			else
			{
				s4.s[0] = s4.p[0] + 1;
				s4.s1[0] = s4.p[0] + 2;
				s4.stan[2] = 1;
				s4.stan[3] = 1;
			}
		}
		//zabezpieczenia przy losowaniu
		pentla = false;
		if ((s4.s[0] == s1.p[0]) && (s4.s[1] == s1.p[1]))
		{
			pentla = true;
		}
		if ((s4.s[0] == s2.p[0]) && (s4.s[1] == s2.p[1]))
		{
			pentla = true;
		}
		if ((s4.s[0] == s2.k[0]) && (s4.s[1] == s2.k[1]))
		{
			pentla = true;
		}
		if ((s4.k[1] == s1.p[1]) && (s4.k[0] == s1.p[0]))
		{
			pentla = true;
		}
		if ((s4.k[1] == s2.p[1]) && (s4.k[0] == s2.p[0]))
		{
			pentla = true;
		}
		if ((s4.k[1] == s2.k[1]) && (s4.k[0] == s2.k[0]))
		{
			pentla = true;
		}
		if ((s4.k[1] == s3.p[1]) && (s4.k[1] == s3.p[0]))
		{
			pentla = true;
		}
		if ((s4.p[0] == s3.s[0]) && (s4.s[1] == s3.s[1]))
		{
			pentla = true;
		}
		if ((s4.p[0] == s3.k[0]) && (s4.s[1] == s3.k[1]))
		{
			pentla = true;
		}
		if ((s4.p[0] == s4.k[0]) && (s4.s[1] == s4.k[1]))
		{
			pentla = true;
		}
		if ((s4.k[1] < 0) || (s4.k[1] > 6))
		{
			pentla = true;
		}
		if ((s4.p[0] < 0) || (s4.p[0] > 6))
		{
			pentla = true;
		}
		if ((s4.s[1] < 0) || (s4.s[1] > 6))
		{
			pentla = true;
		}
		if ((s4.s1[0] < 0) || (s4.s1[0] > 6))
		{
			pentla = true;
		}
		if ((s4.s[0] == s3.p[0]) && (s4.s[1] == s3.p[1]))
		{
			pentla = true;
		}
		if ((s4.s[0] == s3.s[0]) && (s4.s[1] == s3.s[1]))
		{
			pentla = true;
		}
		if ((s4.s[0] == s3.k[0]) && (s4.s[1] == s3.k[1]))
		{
			pentla = true;
		}
		if ((s4.s1[0] == s3.p[0]) && (s4.s[1] == s3.p[1]))
		{
			pentla = true;
		}
		if ((s4.s1[0] == s3.s[0]) && (s4.s[1] == s3.s[1]))
		{
			pentla = true;
		}
		if ((s4.s1[0] == s3.k[0]) && (s4.s[1] == s3.k[1]))
		{
			pentla = true;
		}

	}
}

//funkcja wyswietlajaca statki przy ustawianiu ich przez gracza (zobacz funckje wypelnienie)
void wyswietlenie_wybieranie(int numberstatku, int kx, int ky, statek1& s1, statek2& s2, statek3& s3, statek4& s4, ALLEGRO_BITMAP* ekran, ALLEGRO_BITMAP* statek11, ALLEGRO_BITMAP* statek22, ALLEGRO_BITMAP* statek33, ALLEGRO_BITMAP* statek44, ALLEGRO_BITMAP* pudlo, ALLEGRO_BITMAP* trafienie, ALLEGRO_BITMAP* celownik)
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_scaled_bitmap(ekran, 0, 0, 1216, 1088, 0, 0, restx, resty, NULL);
	//w zaleznosci od numberstatku wyswietlane sa odpowiednie statki
	//np numberstatku  = 3 to wyswietlany jest statek nr 1 i nr 2 

	if (numberstatku == 0 || numberstatku == 1)
	{
		al_draw_bitmap(statek11, (s1.p[1] * 86) + 340, (s1.p[0] * 74) + 124, NULL);
		al_flip_display();
	}

	if (numberstatku == 2 || numberstatku == 3)
	{
		al_draw_bitmap(statek11, (s1.p[1] * 86) + 340, (s1.p[0] * 74) + 124, NULL);
		al_flip_display();

		if (s2.p[0] == s2.k[0])
		{
			if (s2.p[1] > s2.k[1])
			{
				al_draw_rotated_bitmap(statek22, 64 / 2, 128 / 2, (s2.p[1] * 90) + 315, (s2.p[0] * 74) + 155, 3.14 / 2, NULL);
				al_flip_display();
			}
			else if (s2.p[1] < s2.k[1])
			{
				al_draw_rotated_bitmap(statek22, 64 / 2, 128 / 2, (s2.k[1] * 90) + 315, (s2.k[0] * 74) + 155, 3.14 / 2, NULL);
				al_flip_display();
			}
		}
		else if (s2.p[1] == s2.k[1])
		{
			if (s2.p[0] > s2.k[0])
			{
				al_draw_bitmap(statek22, (s2.k[1] * 86) + 340, (s2.k[0] * 74) + 124, NULL);
				al_flip_display();
			}
			else
			{
				al_draw_bitmap(statek22, (s2.p[1] * 86) + 340, (s2.p[0] * 74) + 124, NULL);
				al_flip_display();
			}
		}
	}

	if (numberstatku == 4 || numberstatku == 5)
	{
		al_draw_bitmap(statek11, (s1.p[1] * 86) + 340, (s1.p[0] * 74) + 124, NULL);
		al_flip_display();

		if (s2.p[0] == s2.k[0])
		{
			if (s2.p[1] > s2.k[1])
			{
				al_draw_rotated_bitmap(statek22, 64 / 2, 128 / 2, (s2.p[1] * 90) + 315, (s2.p[0] * 74) + 155, 3.14 / 2, NULL);
				al_flip_display();
			}
			else if (s2.p[1] < s2.k[1])
			{
				al_draw_rotated_bitmap(statek22, 64 / 2, 128 / 2, (s2.k[1] * 90) + 315, (s2.k[0] * 74) + 155, 3.14 / 2, NULL);
				al_flip_display();
			}
		}
		else if (s2.p[1] == s2.k[1])
		{
			if (s2.p[0] > s2.k[0])
			{
				al_draw_bitmap(statek22, (s2.k[1] * 86) + 340, (s2.k[0] * 74) + 124, NULL);
				al_flip_display();
			}
			else
			{
				al_draw_bitmap(statek22, (s2.p[1] * 86) + 340, (s2.p[0] * 74) + 124, NULL);
				al_flip_display();
			}
		}

		if (s3.p[0] == s3.k[0])
		{
			if (s3.p[1] - s3.k[1] == 2 || s3.p[1] - s3.k[1] == (-2))
			{
				if (s3.p[1] > s3.k[1])
				{
					al_draw_rotated_bitmap(statek33, 64 / 2, 128 / 2, (s3.p[1] * 90) + 315, (s3.p[0] * 74) + 155, 3.14 / 2, NULL);
					al_flip_display();
				}
				else
				{
					al_draw_rotated_bitmap(statek33, 64 / 2, 128 / 2, (s3.k[1] * 90) + 315, (s3.k[0] * 74) + 155, 3.14 / 2, NULL);
					al_flip_display();
				}
			}
		}
		else if (s3.p[1] == s3.k[1])
		{
			if (s3.p[0] - s3.k[0] == 2 || s3.p[0] - s3.k[0] == (-2))
			{
				if (s3.p[0] > s3.k[0])
				{
					al_draw_bitmap(statek33, (s3.k[1] * 86) + 340, (s3.k[0] * 74) + 124, NULL);
					al_flip_display();
				}
				else
				{
					al_draw_bitmap(statek33, (s3.p[1] * 86) + 340, (s3.p[0] * 74) + 124, NULL);
					al_flip_display();
				}
			}
		}





	}

	if (numberstatku == 6)
	{
		al_draw_bitmap(statek11, (s1.p[1] * 86) + 340, (s1.p[0] * 74) + 124, NULL);
		al_flip_display();

		if (s2.p[0] == s2.k[0])
		{
			if (s2.p[1] > s2.k[1])
			{
				al_draw_rotated_bitmap(statek22, 64 / 2, 128 / 2, (s2.p[1] * 90) + 315, (s2.p[0] * 74) + 155, 3.14 / 2, NULL);
				al_flip_display();
			}
			else if (s2.p[1] < s2.k[1])
			{
				al_draw_rotated_bitmap(statek22, 64 / 2, 128 / 2, (s2.k[1] * 90) + 315, (s2.k[0] * 74) + 155, 3.14 / 2, NULL);
				al_flip_display();
			}
		}
		else if (s2.p[1] == s2.k[1])
		{
			if (s2.p[0] > s2.k[0])
			{
				al_draw_bitmap(statek22, (s2.k[1] * 86) + 340, (s2.k[0] * 74) + 124, NULL);
				al_flip_display();
			}
			else
			{
				al_draw_bitmap(statek22, (s2.p[1] * 86) + 340, (s2.p[0] * 74) + 124, NULL);
				al_flip_display();
			}
		}

		if (s3.p[0] == s3.k[0])
		{
			if (s3.p[1] - s3.k[1] == 2 || s3.p[1] - s3.k[1] == (-2))
			{
				if (s3.p[1] > s3.k[1])
				{
					al_draw_rotated_bitmap(statek33, 64 / 2, 128 / 2, (s3.p[1] * 90) + 315, (s3.p[0] * 74) + 155, 3.14 / 2, NULL);
					al_flip_display();
				}
				else
				{
					al_draw_rotated_bitmap(statek33, 64 / 2, 128 / 2, (s3.k[1] * 90) + 315, (s3.k[0] * 74) + 155, 3.14 / 2, NULL);
					al_flip_display();
				}
			}
		}
		else if (s3.p[1] == s3.k[1])
		{
			if (s3.p[0] - s3.k[0] == 2 || s3.p[0] - s3.k[0] == (-2))
			{
				if (s3.p[0] > s3.k[0])
				{
					al_draw_bitmap(statek33, (s3.k[1] * 86) + 340, (s3.k[0] * 74) + 124, NULL);
					al_flip_display();
				}
				else
				{
					al_draw_bitmap(statek33, (s3.p[1] * 86) + 340, (s3.p[0] * 74) + 124, NULL);
					al_flip_display();
				}
			}
		}

		if (s4.p[0] == s4.k[0])
		{
			if (s4.p[1] - s4.k[1] == 3 || s4.p[1] - s4.k[1] == (-3))
			{
				if (s4.p[1] > s4.k[1])
				{
					al_draw_rotated_bitmap(statek44, 64 / 2, 128 / 2, (s4.p[1] * 88) + 305, (s4.p[0] * 74) + 155, 3.14 / 2, NULL);
					al_flip_display();
				}
				else
				{
					al_draw_rotated_bitmap(statek44, 64 / 2, 128 / 2, (s4.k[1] * 88) + 305, (s4.k[0] * 74) + 155, 3.14 / 2, NULL);
					al_flip_display();
				}
			}
		}
		else if (s4.p[1] == s4.k[1])
		{
			if (s4.p[0] - s4.k[0] == 3 || s4.p[0] - s4.k[0] == (-3))
			{
				if (s4.p[0] > s4.k[0])
				{
					al_draw_bitmap(statek44, (s4.k[1] * 86) + 340, (s4.k[0] * 74) + 124, NULL);
					al_flip_display();
				}
				else
				{
					al_draw_bitmap(statek44, (s4.p[1] * 86) + 340, (s4.p[0] * 74) + 124, NULL);
					al_flip_display();
				}
			}
		}
	}

	al_draw_bitmap(celownik, (kx * 86) + 336, (ky * 74) + 118, NULL);
	//al_draw_scaled_bitmap(celownik, 0, 0, 78, 75,(kx * 38) + 817, (ky * 34) + 721, 25, 25, NULL);
	al_flip_display();
}
//funkcja ustawiana statkow przez gracza
void wypelnienie(ALLEGRO_EVENT_QUEUE** event_queue, ALLEGRO_FONT* font8, statek1& s1, statek2& s2, statek3& s3, statek4& s4, int punktyp1, int punktyp2, ALLEGRO_BITMAP* ekran, ALLEGRO_BITMAP* statek11, ALLEGRO_BITMAP* statek22, ALLEGRO_BITMAP* statek33, ALLEGRO_BITMAP* statek44, ALLEGRO_BITMAP* pudlo, ALLEGRO_BITMAP* trafienie, ALLEGRO_BITMAP* celownik)
{
	//numberstatku to ktory statek ustawiamy
	// 1 - s1.p
	// 2 - s2.p
	// 3 - s2.k
	// i tak dalej
	int kx = 0, ky = 0;
	int numberstatku = 0;
	bool pentla = true;
	int i = 0;
	while (i < 7)
	{
		while (pentla)
		{

			wyswietlenie_wybieranie(numberstatku, kx, ky, s1, s2, s3, s4, ekran, statek11, statek22, statek33, statek44, pudlo, trafienie, celownik);

			ALLEGRO_EVENT events;
			al_wait_for_event(*event_queue, &events);
			//za pomoca strzalek zmieniamy kx i ky ktore odpowiada za ustawianie punktow statkow
			if (events.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (events.keyboard.keycode)
				{
				case ALLEGRO_KEY_DOWN:
					if (ky < 6) ky = ky + 1;
					break;
				case ALLEGRO_KEY_UP:
					if (ky > 0) ky = ky - 1;
					break;
				case ALLEGRO_KEY_RIGHT:
					if (kx < 6) kx = kx + 1;
					break;
				case ALLEGRO_KEY_LEFT:
					if (kx > 0) kx = kx - 1;
					break;
				case ALLEGRO_KEY_ENTER:
					pentla = false;
					break;
				}


			}//dalej sa zabezpieczenia 
			if ((numberstatku == 0))
			{
				s1.p[0] = ky;
				s1.p[1] = kx;
				s1.stan = 1;
			}
			if (numberstatku == 1)
			{
				if ((kx == s1.p[1]) && (ky == s1.p[0]))
				{
					pentla = true;
				}
				else
				{
					s2.p[0] = ky;
					s2.p[1] = kx;
					s2.stan[0] = 1;
				}
			}
			if ((numberstatku == 2))
			{
				if ((kx == s1.p[1]) && (ky == s1.p[0]))
				{
					pentla = true;
				}
				if ((kx == s2.p[1]) && (ky == s2.p[0]))
				{
					pentla = true;
				}

				s2.k[0] = ky;
				s2.k[1] = kx;
				s2.stan[1] = 1;

			}
			if (numberstatku == 3)
			{
				if ((kx == s1.p[1]) && (ky == s1.p[0]))
				{
					pentla = true;
				}
				if ((kx == s2.p[1]) && (ky == s2.p[0]))
				{
					pentla = true;
				}
				if ((kx == s2.k[1]) && (ky == s2.k[0]))
				{
					pentla = true;
				}

				s3.p[0] = ky;
				s3.p[1] = kx;
				s3.stan[0] = 1;
			}
			if (numberstatku == 4)
			{
				s3.k[0] = ky;
				s3.k[1] = kx;
				s3.stan[2] = 1;

				if (s3.p[0] == s3.k[0])
				{
					s3.s[0] = s3.p[0];
					s3.s[1] = (s3.p[1] + s3.k[1]) / 2;
					s3.stan[1] = 1;
				}
				else
				{
					s3.s[1] = s3.p[1];
					s3.s[0] = (s3.p[0] + s3.k[0]) / 2;
					s3.stan[1] = 1;
				}
				if ((s3.s[0] == s1.p[0]) && (s3.s[1] == s1.p[1]))
				{
					pentla = true;
				}
				if ((s3.s[0] == s2.p[0]) && (s3.s[1] == s2.p[1]))
				{
					pentla = true;
				}
				if ((s3.s[0] == s2.k[0]) && (s3.s[1] == s2.k[1]))
				{
					pentla = true;
				}
				if ((kx == s1.p[1]) && (ky == s1.p[0]))
				{
					pentla = true;
				}
				if ((kx == s2.p[1]) && (ky == s2.p[0]))
				{
					pentla = true;
				}
				if ((kx == s2.k[1]) && (ky == s2.k[0]))
				{
					pentla = true;
				}
				if ((kx == s3.p[1]) && (ky == s3.p[0]))
				{
					pentla = true;
				}
				if ((s3.s[1] == s3.p[1]) && (s3.s[1] == s3.p[0]))
				{
					pentla = true;
				}
			}
			if (numberstatku == 5)
			{
				if ((kx == s1.p[1]) && (ky == s1.p[0]))
				{
					pentla = true;
				}
				if ((kx == s2.p[1]) && (ky == s2.p[0]))
				{
					pentla = true;
				}
				if ((kx == s2.k[1]) && (ky == s2.k[0]))
				{
					pentla = true;
				}
				if ((kx == s3.p[1]) && (ky == s3.p[0]))
				{
					pentla = true;
				}
				if ((kx == s3.s[1]) && (ky == s3.s[0]))
				{
					pentla = true;
				}
				if ((kx == s3.k[1]) && (ky == s3.k[0]))
				{
					pentla = true;
				}

				s4.p[0] = ky;
				s4.p[1] = kx;
				s4.stan[0] = 1;
			}

			if (numberstatku == 6)
			{
				if ((kx == s1.p[1]) && (ky == s1.p[0]))
				{
					pentla = true;
				}
				if ((kx == s2.p[1]) && (ky == s2.p[0]))
				{
					pentla = true;
				}
				if ((kx == s2.k[1]) && (ky == s2.k[0]))
				{
					pentla = true;
				}
				if ((kx == s3.p[1]) && (ky == s3.p[0]))
				{
					pentla = true;
				}
				if ((kx == s3.s[1]) && (ky == s3.s[0]))
				{
					pentla = true;
				}
				if ((kx == s3.k[1]) && (ky == s3.k[0]))
				{
					pentla = true;
				}

				s4.k[0] = ky;
				s4.k[1] = kx;
				s4.stan[1] = 1;

				if (s4.p[0] == s4.k[0])
				{
					s4.s[0] = s4.p[0];
					s4.s1[0] = s4.p[0];

					if (s4.p[1] > s4.k[1])
					{
						s4.s[1] = s4.p[1] - 1;
						s4.s1[1] = s4.p[1] - 2;
						s4.stan[2] = 1;
						s4.stan[3] = 1;
					}
					else
					{
						s4.s[1] = s4.p[1] + 1;
						s4.s1[1] = s4.p[1] + 2;
						s4.stan[2] = 1;
						s4.stan[3] = 1;
					}
				}
				else
				{
					s4.s[1] = s4.p[1];
					s4.s1[1] = s4.p[1];
					if (s4.p[0] > s4.k[0])
					{
						s4.s[0] = s4.p[0] - 1;
						s4.s1[0] = s4.p[0] - 2;
						s4.stan[2] = 1;
						s4.stan[3] = 1;
					}
					else
					{
						s4.s[0] = s4.p[0] + 1;
						s4.s1[0] = s4.p[0] + 2;
						s4.stan[2] = 1;
						s4.stan[3] = 1;
					}
				}
			}

		}

		numberstatku = numberstatku + 1;
		printf("i=%d\n", i);
		i = i + 1;
		pentla = true;

	}

}
//wyswietlanie wyszystkiego podczas gry 
void wyswietlenie(statek1 s1, statek2 s2, statek3 s3, statek4 s4, int kx, int ky, int punktyp1, int punktyp2, ALLEGRO_FONT** font8, ALLEGRO_BITMAP* ekran, ALLEGRO_BITMAP* statek11, ALLEGRO_BITMAP* statek22, ALLEGRO_BITMAP* statek33, ALLEGRO_BITMAP* statek44, ALLEGRO_BITMAP* pudlo, ALLEGRO_BITMAP* trafienie, ALLEGRO_BITMAP* celownik, list<int> historiax, list<int> historiay, list<int> historiatraf)
{

	//funkcja wyswietlajaca wszystko podczas gry
	//
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_rectangle(0, 0, restx, resty, al_map_rgb(25, 30, 150), 50);
	al_draw_textf(*font8, al_map_rgb(0, 255, 255), 100, 5, ALLEGRO_ALIGN_CENTER, "GRACZ NR 1: %d", punktyp1);
	al_draw_textf(*font8, al_map_rgb(0, 255, 255), 300, 5, ALLEGRO_ALIGN_CENTER, "GRACZ NR 2: %d", punktyp2);
	al_flip_display();

	al_draw_scaled_bitmap(ekran, 0, 0, 1216, 1088, 0, 0, restx, resty, NULL);
	al_flip_display();


	if (s1.stan == 1)
	{
		al_draw_bitmap(statek11, (s1.p[1] * 86) + 340, (s1.p[0] * 74) + 124, NULL);
		al_flip_display();
	}
	else
	{
		al_draw_bitmap(statek11, (s1.p[1] * 86) + 340, (s1.p[0] * 74) + 124, NULL);
		al_draw_bitmap(trafienie, (s1.p[1] * 86) + 334, (s1.p[0] * 74) + 119, NULL);
		al_flip_display();
	}

	//statek2
	if (s2.stan[0] && s2.stan[1])
	{
		if (s2.p[0] == s2.k[0])
		{
			if (s2.p[1] > s2.k[1])
			{
				al_draw_rotated_bitmap(statek22, 64 / 2, 128 / 2, (s2.p[1] * 90) + 315, (s2.p[0] * 74) + 155, 3.14 / 2, NULL);
				al_flip_display();
			}
			else if (s2.p[1] < s2.k[1])
			{
				al_draw_rotated_bitmap(statek22, 64 / 2, 128 / 2, (s2.k[1] * 90) + 315, (s2.k[0] * 74) + 155, 3.14 / 2, NULL);
				al_flip_display();
			}
		}
		else if (s2.p[1] == s2.k[1])
		{
			if (s2.p[0] > s2.k[0])
			{
				al_draw_bitmap(statek22, (s2.k[1] * 86) + 340, (s2.k[0] * 74) + 124, NULL);
				al_flip_display();
			}
			else
			{
				al_draw_bitmap(statek22, (s2.p[1] * 86) + 340, (s2.p[0] * 74) + 124, NULL);
				al_flip_display();
			}
		}
	}
	else
	{
		if (s2.p[0] == s2.k[0])
		{
			if (s2.p[1] > s2.k[1])
			{
				al_draw_rotated_bitmap(statek22, 64 / 2, 128 / 2, (s2.p[1] * 90) + 315, (s2.p[0] * 74) + 155, 3.14 / 2, NULL);
				if (s2.stan[1] == 0 && s2.stan[0] == 0)
				{
					al_draw_bitmap(trafienie, (s2.p[1] * 86) + 334, (s2.p[0] * 74) + 119, NULL);
					al_draw_bitmap(trafienie, (s2.k[1] * 86) + 334, (s2.k[0] * 74) + 119, NULL);
				}
				else if (s2.stan[0] == 0)
				{
					al_draw_bitmap(trafienie, (s2.p[1] * 86) + 334, (s2.p[0] * 74) + 119, NULL);
				}
				else
				{
					al_draw_bitmap(trafienie, (s2.k[1] * 86) + 334, (s2.k[0] * 74) + 119, NULL);
				}
				al_flip_display();
			}
			else
			{
				al_draw_rotated_bitmap(statek22, 64 / 2, 128 / 2, (s2.k[1] * 90) + 315, (s2.k[0] * 74) + 155, 3.14 / 2, NULL);
				if (s2.stan[1] == 0 && s2.stan[0] == 0)
				{
					al_draw_bitmap(trafienie, (s2.p[1] * 86) + 334, (s2.p[0] * 74) + 119, NULL);
					al_draw_bitmap(trafienie, (s2.k[1] * 86) + 334, (s2.k[0] * 74) + 119, NULL);
				}
				else if (s2.stan[0] == 0)
				{
					al_draw_bitmap(trafienie, (s2.p[1] * 86) + 334, (s2.p[0] * 74) + 119, NULL);
				}
				else
				{
					al_draw_bitmap(trafienie, (s2.k[1] * 86) + 334, (s2.k[0] * 74) + 119, NULL);
				}
				al_flip_display();
			}
		}
		else
		{
			if (s2.p[0] > s2.k[0])
			{
				al_draw_bitmap(statek22, (s2.k[1] * 86) + 340, (s2.k[0] * 74) + 124, NULL);
				if (s2.stan[1] == 0 && s2.stan[0] == 0)
				{
					al_draw_bitmap(trafienie, (s2.p[1] * 86) + 334, (s2.p[0] * 74) + 119, NULL);
					al_draw_bitmap(trafienie, (s2.k[1] * 86) + 334, (s2.k[0] * 74) + 119, NULL);
				}
				else if (s2.stan[0] == 0)
				{
					al_draw_bitmap(trafienie, (s2.p[1] * 86) + 334, (s2.p[0] * 74) + 119, NULL);
				}
				else
				{
					al_draw_bitmap(trafienie, (s2.k[1] * 86) + 334, (s2.k[0] * 74) + 119, NULL);
				}
				al_flip_display();
			}
			else
			{
				al_draw_bitmap(statek22, (s2.p[1] * 86) + 340, (s2.p[0] * 74) + 124, NULL);
				if (s2.stan[1] == 0 && s2.stan[0] == 0)
				{
					al_draw_bitmap(trafienie, (s2.p[1] * 86) + 334, (s2.p[0] * 74) + 119, NULL);
					al_draw_bitmap(trafienie, (s2.k[1] * 86) + 334, (s2.k[0] * 74) + 119, NULL);
				}
				else if (s2.stan[0] == 0)
				{
					al_draw_bitmap(trafienie, (s2.p[1] * 86) + 334, (s2.p[0] * 74) + 119, NULL);
				}
				else
				{
					al_draw_bitmap(trafienie, (s2.k[1] * 86) + 334, (s2.k[0] * 74) + 119, NULL);
				}
				al_flip_display();
			}
		}
	}

	//statek3
	if (s3.stan[0] && s3.stan[1] && s3.stan[2])
	{
		if (s3.p[0] == s3.k[0])
		{
			if (s3.p[1] > s3.k[1])
			{
				al_draw_rotated_bitmap(statek33, 64 / 2, 128 / 2, (s3.p[1] * 90) + 315, (s3.p[0] * 74) + 155, 3.14 / 2, NULL);
				al_flip_display();
			}
			else
			{
				al_draw_rotated_bitmap(statek33, 64 / 2, 128 / 2, (s3.k[1] * 90) + 315, (s3.k[0] * 74) + 155, 3.14 / 2, NULL);
				al_flip_display();
			}
		}
		else
		{
			if (s3.p[0] > s3.k[0])
			{
				al_draw_bitmap(statek33, (s3.k[1] * 86) + 340, (s3.k[0] * 74) + 124, NULL);
				al_flip_display();
			}
			else
			{
				al_draw_bitmap(statek33, (s3.p[1] * 86) + 340, (s3.p[0] * 74) + 124, NULL);
				al_flip_display();
			}
		}
	}
	else
	{
		if (s3.p[0] == s3.k[0])
		{
			if (s3.p[1] > s3.k[1])
			{
				al_draw_rotated_bitmap(statek33, 64 / 2, 128 / 2, (s3.p[1] * 90) + 315, (s3.p[0] * 74) + 155, 3.14 / 2, NULL);
				if (s3.stan[1] == 0)
				{
					al_draw_bitmap(trafienie, (s3.s[1] * 86) + 334, (s3.s[0] * 74) + 119, NULL);
				}
				if (s3.stan[0] == 0)
				{
					al_draw_bitmap(trafienie, (s3.p[1] * 86) + 334, (s3.p[0] * 74) + 119, NULL);
				}
				if (s3.stan[2] == 0)
				{
					al_draw_bitmap(trafienie, (s3.k[1] * 86) + 334, (s3.k[0] * 74) + 119, NULL);
				}
				al_flip_display();
			}
			else
			{
				al_draw_rotated_bitmap(statek33, 64 / 2, 128 / 2, (s3.k[1] * 90) + 315, (s3.k[0] * 74) + 155, 3.14 / 2, NULL);
				if (s3.stan[1] == 0)
				{
					al_draw_bitmap(trafienie, (s3.s[1] * 86) + 334, (s3.s[0] * 74) + 119, NULL);
				}
				if (s3.stan[0] == 0)
				{
					al_draw_bitmap(trafienie, (s3.p[1] * 86) + 334, (s3.p[0] * 74) + 119, NULL);
				}
				if (s3.stan[2] == 0)
				{
					al_draw_bitmap(trafienie, (s3.k[1] * 86) + 334, (s3.k[0] * 74) + 119, NULL);
				}
				al_flip_display();
			}
		}
		else
		{
			if (s3.p[0] > s3.k[0])
			{
				al_draw_bitmap(statek33, (s3.k[1] * 86) + 340, (s3.k[0] * 74) + 124, NULL);
				if (s3.stan[1] == 0)
				{
					al_draw_bitmap(trafienie, (s3.s[1] * 86) + 334, (s3.s[0] * 74) + 119, NULL);
				}
				if (s3.stan[0] == 0)
				{
					al_draw_bitmap(trafienie, (s3.p[1] * 86) + 334, (s3.p[0] * 74) + 119, NULL);
				}
				if (s3.stan[2] == 0)
				{
					al_draw_bitmap(trafienie, (s3.k[1] * 86) + 334, (s3.k[0] * 74) + 119, NULL);
				}
			}
			else
			{
				al_draw_bitmap(statek33, (s3.p[1] * 86) + 340, (s3.p[0] * 74) + 124, NULL);
				if (s3.stan[1] == 0)
				{
					al_draw_bitmap(trafienie, (s3.s[1] * 86) + 334, (s3.s[0] * 74) + 119, NULL);
				}
				if (s3.stan[0] == 0)
				{
					al_draw_bitmap(trafienie, (s3.p[1] * 86) + 334, (s3.p[0] * 74) + 119, NULL);
				}
				if (s3.stan[2] == 0)
				{
					al_draw_bitmap(trafienie, (s3.k[1] * 86) + 334, (s3.k[0] * 74) + 119, NULL);
				}
				al_flip_display();
			}
		}
	}

	if (s4.p[0] == s4.k[0])
	{
		if (s4.p[1] - s4.k[1] == 3 || s4.p[1] - s4.k[1] == (-3))
		{
			if (s4.p[1] > s4.k[1])
			{
				al_draw_rotated_bitmap(statek44, 64 / 2, 128 / 2, (s4.p[1] * 88) + 305, (s4.p[0] * 74) + 155, 3.14 / 2, NULL);
				al_flip_display();
			}
			else
			{
				al_draw_rotated_bitmap(statek44, 64 / 2, 128 / 2, (s4.k[1] * 88) + 305, (s4.k[0] * 74) + 155, 3.14 / 2, NULL);
				al_flip_display();
			}
		}
	}
	else if (s4.p[1] == s4.k[1])
	{
		if (s4.p[0] - s4.k[0] == 3 || s4.p[0] - s4.k[0] == (-3))
		{
			if (s4.p[0] > s4.k[0])
			{
				al_draw_bitmap(statek44, (s4.k[1] * 86) + 340, (s4.k[0] * 74) + 124, NULL);
				al_flip_display();
			}
			else
			{
				al_draw_bitmap(statek44, (s4.p[1] * 86) + 340, (s4.p[0] * 74) + 124, NULL);
				al_flip_display();
			}
		}
	}

	//wyswietlanie iksa jesli statek zostal trafiony
	if (s4.stan[0] == 0)
	{
		al_draw_bitmap(trafienie, (s4.p[1] * 86) + 334, (s4.p[0] * 74) + 119, NULL);
		al_flip_display();
	}
	if (s4.stan[1] == 0)
	{
		al_draw_bitmap(trafienie, (s4.s[1] * 86) + 334, (s4.s[0] * 74) + 119, NULL);
		al_flip_display();
	}
	if (s4.stan[2] == 0)
	{
		al_draw_bitmap(trafienie, (s4.s1[1] * 86) + 334, (s4.s1[0] * 74) + 119, NULL);
		al_flip_display();
	}
	if (s4.stan[3] == 0)
	{
		al_draw_bitmap(trafienie, (s4.k[1] * 86) + 334, (s4.k[0] * 74) + 119, NULL);
		al_flip_display();
	}
	
	al_flip_display();

	list<int>::iterator x1;
	list<int>::iterator y1;
	list<int>::iterator traf;

	//wyswietlanie trafien i pudel na podstawie histori
	y1 = historiay.begin();
	traf = historiatraf.begin();
	for (x1 = historiax.begin(); x1 != historiax.end(); ++x1)
	{
		if (y1 != historiay.end())
		{
			if (traf != historiatraf.end())
			{
				if (*traf == 1)
				{
					al_draw_tinted_scaled_bitmap(trafienie, al_map_rgba_f(0, 1, 0.3, 1), 0, 0, 78, 75, (*x1 * 38) + 817, (*y1 * 34) + 721, 25, 25, NULL);
				}
				else
				{
					//al_draw_bitmap(pudlo, (*x1 * 38) + 817, (*y1 * 34) + 721, NULL);
					al_draw_tinted_scaled_bitmap(pudlo, al_map_rgba_f(0, 1, 0.3, 1), 0, 0, 78, 75, (*x1 * 38) + 817, (*y1 * 34) + 721, 25, 25, NULL);
				}
				al_flip_display();
				traf++;
				y1++;
			}
		}
		
	}

	//wyswietlanie punktow graczy
	al_draw_textf(*font8, al_map_rgb(0, 0, 90), 450, 20, ALLEGRO_ALIGN_CENTER, "Punkty P1 : %d",punktyp1);
	al_draw_textf(*font8, al_map_rgb(0, 0, 90), 800, 20, ALLEGRO_ALIGN_CENTER, "Punkty P2 : %d",punktyp2);
	//wyswietlanie celownika
	al_draw_scaled_bitmap(celownik, 0, 0, 78, 75, (kx * 38) + 817, (ky * 34) + 721, 25, 25, NULL);
	al_flip_display();

	//wyswietlanie hp statkow
	al_draw_textf(*font8, al_map_rgb(0, 0, 90), 140, 765, ALLEGRO_ALIGN_CENTER, "%d", s1.stan);
	al_draw_textf(*font8, al_map_rgb(0, 0, 90), 665, 765, ALLEGRO_ALIGN_CENTER, "%d", s4.stan[0] + s4.stan[1] + s4.stan[2] + s4.stan[3]);
	al_draw_textf(*font8, al_map_rgb(0, 0, 90), 280, 880, ALLEGRO_ALIGN_CENTER, "%d", s2.stan[0] + s2.stan[1]);
	al_draw_textf(*font8, al_map_rgb(0, 0, 90), 665, 880, ALLEGRO_ALIGN_CENTER, "%d", s3.stan[0] + s3.stan[1] + s3.stan[2]);
	al_flip_display();


}
//celowanie podczas gry ,dziala na podobnej zasadzie co funkcja "wypelnienie"
void celowanie(statek1 s1, statek2 s2, statek3 s3, statek4 s4, ALLEGRO_EVENT_QUEUE** event_queue, int* kx, int* ky, ALLEGRO_FONT* font8, int punktyp1, int punktyp2, ALLEGRO_BITMAP* ekran, ALLEGRO_BITMAP* statek11, ALLEGRO_BITMAP* statek22, ALLEGRO_BITMAP* statek33, ALLEGRO_BITMAP* statek44, ALLEGRO_BITMAP* pudlo, ALLEGRO_BITMAP* trafienie, ALLEGRO_BITMAP* celownik, list<int> historiax, list<int> historiay, list<int> historiatraf)
{
	*kx = 2;
	*ky = 2;
	bool pentla = true;
	while (pentla)
	{
		wyswietlenie(s1, s2, s3, s4, *kx, *ky, punktyp1, punktyp2, &font8, ekran, statek11, statek22, statek33, statek44, pudlo, trafienie, celownik, historiax, historiay, historiatraf);

		ALLEGRO_EVENT events;
		al_wait_for_event(*event_queue, &events);

		if (events.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (events.keyboard.keycode)
			{
			case ALLEGRO_KEY_DOWN:
				if (*ky < 6) *ky = *ky + 1;
				break;
			case ALLEGRO_KEY_UP:
				if (*ky > 0) *ky = *ky - 1;
				break;
			case ALLEGRO_KEY_RIGHT:
				if (*kx < 6) *kx = *kx + 1;
				break;
			case ALLEGRO_KEY_LEFT:
				if (*kx > 0) *kx = *kx - 1;
				break;
			case ALLEGRO_KEY_ENTER:
				pentla = false;
				break;
			}


		}
	}


}

//sprawdzanie czy strzal zostal trafiony
void strzal(statek1& s1, statek2& s2, statek3& s3, statek4& s4, int kx, int ky, int* punkty, ALLEGRO_FONT** font8,int *tx,int *ty,int *traf, list<int> historiatraf)
{
	//jestli zostal trafiony to stan punktu zmienia sie na 0 
	int czy_traf = 0;
	//statek1
	if (s1.stan)
	{
		if ((s1.p[0] == ky) && (s1.p[1] == kx))
		{
			s1.stan = 0;
			*punkty = *punkty + 1;
			czy_traf = 1;

		}
	}
	//statek2
	if (s2.stan[0])
	{
		if ((s2.p[0] == ky) && (s2.p[1] == kx))
		{
			s2.stan[0] = 0;
			*punkty = *punkty + 1;
			czy_traf = 1;
		}
	}

	if (s2.stan[1])
	{
		if ((s2.k[0] == ky) && (s2.k[1] == kx))
		{
			s2.stan[1] = 0;
			*punkty = *punkty + 1;
			czy_traf = 1;
		}
	}
	//statek3

	if (s3.stan[0])
	{
		if ((s3.p[0] == ky) && (s3.p[1] == kx))
		{
			s3.stan[0] = 0;
			*punkty = *punkty + 1;
			czy_traf = 1;
		}
	}

	if (s3.stan[1])
	{
		if ((s3.s[0] == ky) && (s3.s[1] == kx))
		{
			s3.stan[1] = 0;
			*punkty = *punkty + 1;
			czy_traf = 1;
		}
	}
	if (s3.stan[2])
	{
		if ((s3.k[0] == ky) && (s3.k[1] == kx))
		{
			s3.stan[2] = 0;
			*punkty = *punkty + 1;
			czy_traf = 1;
		}
	}


	if (s4.stan[0])
	{
		if ((s4.p[0] == ky) && (s4.p[1] == kx))
		{
			s4.stan[0] = 0;
			*punkty = *punkty + 1;
			czy_traf = 1;
		}
	}
	if (s4.stan[1])
	{
		if ((s4.s[0] == ky) && (s4.s[1] == kx))
		{
			s4.stan[1] = 0;
			*punkty = *punkty + 1;
			czy_traf = 1;
		}
	}
	if (s4.stan[2])
	{
		if ((s4.s1[0] == ky) && (s4.s1[1] == kx))
		{
			s4.stan[2] = 0;
			*punkty = *punkty + 1;
			czy_traf = 1;
		}
	}
	if (s4.stan[3])
	{
		if ((s4.k[0] == ky) && (s4.k[1] == kx))
		{
			s4.stan[3] = 0;
			*punkty = *punkty + 1;
			czy_traf = 1;
		}
	}

	if (czy_traf)
	{
		//tx i ty to ostatni trafiony strzal przez pc 
		//jest to tylko uzywane do gry z komputerem
		*tx = kx;
		*ty = ky;
		*traf = 1;
		historiatraf.push_back(1);
		al_draw_text(*font8, al_map_rgb(34, 139, 34), restx / 2, resty / 2 - 50, ALLEGRO_ALIGN_CENTER, "STRZAL TRAFIONY");
		al_flip_display();
		Sleep(1000);
	}
	else
	{
		historiatraf.push_back(0);
		al_draw_text(*font8, al_map_rgb(250, 50, 50), restx / 2, resty / 2 - 50, ALLEGRO_ALIGN_CENTER, "STRZAL NIE TRAFIOBY");
		al_flip_display();
		Sleep(1000);
	}

}

//wyswietlanie zmiany ruchu na ekranie 
void zamiana_ruchu(ALLEGRO_FONT** font8)
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_rectangle(0, 0, restx, resty, al_map_rgb(25, 30, 150), 50);
	al_flip_display();
	int i;
	for (i = 5; i > 0; i--)
	{
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_textf(*font8, al_map_rgb(0, 255, 255), restx / 2, resty / 2 - 50, ALLEGRO_ALIGN_CENTER, "RUCH NASTEPNEGO GARCZA! ZA %d", i);
		al_flip_display();
		Sleep(1000);
	}
}

//ekran koncowy gry
void koniec_gry(ALLEGRO_FONT** font8, int punktyp1, int punktyp2, ALLEGRO_EVENT_QUEUE** event_queue)
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	if (punktyp1 > punktyp2)
	{
		al_draw_text(*font8, al_map_rgb(0, 255, 255), restx / 2, resty / 2 - 50, ALLEGRO_ALIGN_CENTER, "WYGRAL GRACZ NR 1");
		al_flip_display();
	}
	else
	{
		al_draw_text(*font8, al_map_rgb(0, 255, 255), restx / 2, resty / 2 - 50, ALLEGRO_ALIGN_CENTER, "WYGRAL GRACZ NR 2");
		al_flip_display();
	}

	al_draw_text(*font8, al_map_rgb(0, 255, 255), restx / 2, resty / 2 + 50, ALLEGRO_ALIGN_CENTER, "NACISNIJ ENTER ABY WYJSC");
	al_flip_display();
	bool pentla = true;
	while (pentla)
	{
		ALLEGRO_EVENT events;
		al_wait_for_event(*event_queue, &events);

		if (events.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (events.keyboard.keycode)
			{
			case ALLEGRO_KEY_ENTER:
				pentla = false;
				break;
			}


		}
	}

}

//ekran poczatkowy gry
void poczatek_gry(ALLEGRO_FONT** font8, int* komputer, ALLEGRO_EVENT_QUEUE** event_queue, ALLEGRO_BITMAP* start)
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	al_draw_scaled_bitmap(start, 0, 0, 1280, 1024, 0, 0, restx, resty, NULL);
	al_draw_text(*font8, al_map_rgb(0, 0, 0), restx / 2, resty / 2 + 160, ALLEGRO_ALIGN_CENTER, "Nacisnij 1 aby zagrac z komputerem");
	al_draw_text(*font8, al_map_rgb(0, 0, 0), restx / 2, resty / 2 + 210, ALLEGRO_ALIGN_CENTER, "Nacisnij 2 aby zagrac z czlowiekiem");
	al_flip_display();
	bool pentla = true;
	while (pentla)
	{
		ALLEGRO_EVENT events;
		al_wait_for_event(*event_queue, &events);

		if (events.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (events.keyboard.keycode)
			{
			case ALLEGRO_KEY_1:
				*komputer = 1;
				pentla = false;
				break;

			case ALLEGRO_KEY_2:
				*komputer = 0;
				pentla = false;
				break;
			}


		}
	}

	if (*komputer == 1)
	{
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_flip_display();
		al_draw_scaled_bitmap(start, 0, 0, 1280, 1024, 0, 0, restx, resty, NULL);
		al_draw_text(*font8, al_map_rgb(0, 0, 0), restx / 2, resty / 2 + 160, ALLEGRO_ALIGN_CENTER, "Nacisnij 1 - latwy poziom trudnosci");
		al_draw_text(*font8, al_map_rgb(0, 0, 0), restx / 2, resty / 2 + 210, ALLEGRO_ALIGN_CENTER, "Nacisnij 2 - ciezki poziom trudnosci");
		pentla = true;
		al_flip_display();
		while (pentla)
		{
			ALLEGRO_EVENT events;
			al_wait_for_event(*event_queue, &events);

			if (events.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (events.keyboard.keycode)
				{
				case ALLEGRO_KEY_1:
					*komputer = 1;
					pentla = false;
					break;

				case ALLEGRO_KEY_2:
					*komputer = 2;
					pentla = false;
					break;
				}


			}
		}
	}

}

//zmiana ruchu jesli naszym przeciwnikiem jest pc
void strzal_pc(ALLEGRO_FONT* font8)
{

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	al_draw_textf(font8, al_map_rgb(0, 255, 255), restx / 2, resty / 2 - 100, ALLEGRO_ALIGN_CENTER, "RUCH KOMPUTERA", NULL);
	al_flip_display();
	Sleep(2000);

}

//strzal inteligentnego pc
void pc_strzal(int* kx, int* ky, statek1 s1, statek2 s2, statek3 s3, statek4 s4, int* tx, int* ty,int *traf, list<int> historiaxp2, list<int> historiayp2)
{
	//jesli pc trafi strzal to na jego podstawie strzela do okola tego punktu
	//zmienna traf mowi nam czy mamy strzelac do okola punktu ostaniego trafienia czy nie
	int i;
	int pentla = 1;
	int ile = 0;
	srand(time(0));
	list<int>::iterator x1;
	list<int>::iterator y1;
	cout << "stare" << endl;
	cout << "kx = " << *kx << endl;
	cout << "ky = " << *ky << endl;
	cout << "tx = " << *tx << endl;
	cout << "ty = " << *ty << endl<<endl;
	if (*traf == 1)
	{
		cout << "weszlo";
		while (pentla)
		{
			//losowanie ktory punkt w bedzie strzalem ale bedzie to punkty oddalony o 1 od ostatniego trafienia
			i = rand() % 4;
			if (i == 0)
			{
				*kx = *tx - 1;
				*ky = *ty;
			}
			if (i == 1)
			{
				*kx = *tx;
				*ky = *ty-1;
			}
			if (i == 2)
			{
				*kx = *tx + 1;
				*ky = *ty;
			}
			if (i == 3)
			{
				*kx = *tx;
				*ky = *ty+ 1;
			}

			//zabezpieczenia
			pentla = 0;
			if (*kx < 0 || *kx>6) pentla = 1;
			if (*kx < 0 || *ky>6) pentla = 1;
			y1 = historiayp2.begin();
			//nie strzelamy dwa razy w to samo
			for (x1 = historiaxp2.begin(); x1 != historiaxp2.end(); ++x1)
			{
				if ((*x1 == *kx) && (*y1 == *kx))
				{
					pentla = 1;
					ile = ile + 1;
				}
				y1++;
			}
			//tu jest zabezpieczenie jezeli w okół ostatniego trafienia nie ma juz wolnych punktów do strzelania
			if (ile == 4)
			{
				*kx = rand() % 7;
				*ky = rand() % 7;
				pentla = 0;
				*traf = 0;
			}
			else if (ile == 3)
			{
				if ((*kx == 0) || (*kx == 6))
				{
					*kx = rand() % 7;
					*ky = rand() % 7;
					pentla = 0;
					*traf = 0;
				}
				else if ((*kx == 0) || (*kx == 6))
				{
					*kx = rand() % 7;
					*ky = rand() % 7;
					pentla = 0;
					*traf = 0;
				}
			}
			else if (ile == 2)
			{
				if ((*kx == 0) && (*ky == 0))
				{
					*kx = rand() % 7;
					*ky = rand() % 7;
					pentla = 0;
					*traf = 0;
				}

				if ((*kx == 0) && (*ky == 6))
				{
					*kx = rand() % 7;
					*ky = rand() % 7;
					pentla = 0;
					*traf = 0;
				}

				if ((*kx == 6) && (*ky == 0))
				{
					*kx = rand() % 7;
					*ky = rand() % 7;
					pentla = 0;
					*traf = 0;
				}

				if ((*kx == 6) && (*ky == 6))
				{
					*kx = rand() % 7;
					*ky = rand() % 7;
					pentla = 0;
					*traf = 0;
				}
			}

		}
	}
	else
	{
	//jestli nie ma jeszcze pierwszego trafienia albo pozbylismy sie wolnych punktow do trafienia
		*kx = rand() % 7;
		*ky = rand() % 7;
	}
	cout<<"nowe" << endl;
	cout << "kx = " << *kx << endl;
	cout << "ky = " << *ky << endl;
	
}

int main()
{
	al_init();
	al_install_keyboard();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_shutdown_image_addon();

	ALLEGRO_DISPLAY* okno = al_create_display(restx, resty);
	ALLEGRO_TIMER* timer = al_create_timer(3.0 / 60.0);
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	//ALLEGRO_EVENT events;

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(okno));

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_rectangle(0, 0, restx, resty, al_map_rgb(25, 30, 150), 50);
	al_flip_display();

	char const* filename = { "MinecraftTen-VGORe.ttf" };
	ALLEGRO_FONT* font8 = al_load_ttf_font(filename, 40, ALLEGRO_TTF_NO_AUTOHINT);
	ALLEGRO_BITMAP* start = al_load_bitmap("EkranStart.png");
	ALLEGRO_BITMAP* ekran = al_load_bitmap("EkranGry.png");
	ALLEGRO_BITMAP* statek11 = al_load_bitmap("1x1.png");
	ALLEGRO_BITMAP* statek22 = al_load_bitmap("2x1.png");
	ALLEGRO_BITMAP* statek33 = al_load_bitmap("3x1.png");
	ALLEGRO_BITMAP* statek44 = al_load_bitmap("4x1.png");
	ALLEGRO_BITMAP* pudlo = al_load_bitmap("PudloDuze.png");
	ALLEGRO_BITMAP* trafienie = al_load_bitmap("TrafienieDuze.png");
	ALLEGRO_BITMAP* celownik = al_load_bitmap("celownik.png");

	int komputer = 0;
	int punktyp1, punktyp2;
	int prevp1, prevp2;
	int kx = 2;
	int ky = 2;
	int tx = (- 1);
	int ty = (- 1);
	int traf = 0;
	int bladx;
	int blady;
	punktyp1 = punktyp2 = 0;
	bool pentla_gra = true;
	double sum = 0;
	double add = 1;

	statek1 g1s1;
	statek1 g2s1;

	statek2 g1s2;
	statek2 g2s2;

	statek3 g1s3;
	statek3 g2s3;

	statek4 g1s4;
	statek4 g2s4;

	list<int> historiaxp1;
	list<int> historiayp1;
	list<int> historiatraf;

	list<int> historiaxp2;
	list<int> historiayp2;

	list<int>::iterator x1;
	list<int>::iterator y1;

	poczatek_gry(&font8, &komputer, &event_queue, start);

	//wypelnianie statkow
	if (komputer == 0)
	{
		wypelnienie(&event_queue, font8, g1s1, g1s2, g1s3, g1s4, punktyp1, punktyp2, ekran, statek11, statek22, statek33, statek44, pudlo, trafienie,celownik);
		wypelnienie(&event_queue, font8, g2s1, g2s2, g2s3, g2s4, punktyp1, punktyp2, ekran, statek11, statek22, statek33, statek44, pudlo, trafienie,celownik);
		
		printf("s1 = x%d y%d\n", g2s1.p[0], g2s1.p[1]);

		printf("s2 p = x%d y%d\n", g2s2.p[0], g2s2.p[1]);
		printf("s2 k = x%d y%d\n", g2s2.k[0], g2s2.k[1]);

		printf("s3 p = x%d y%d\n", g2s3.p[0], g2s3.p[1]);
		printf("s3 s = x%d y%d\n", g2s3.s[0], g2s3.s[1]);
		printf("s3 k = x%d y%d\n", g2s3.k[0], g2s3.k[1]);

		printf("s4 p = x%d y%d\n", g2s4.p[0], g2s4.p[1]);
		printf("s4 s = x%d y%d\n", g2s4.s[0], g2s4.s[1]);
		printf("s4 s1 = x%d y%d\n", g2s4.s1[0], g2s4.s1[1]);
		printf("s4 p = x%d y%d\n", g2s4.k[0], g2s4.k[1]);
	}
	else
	{
		wypelnienie(&event_queue, font8, g1s1, g1s2, g1s3, g1s4, punktyp1, punktyp2, ekran, statek11, statek22, statek33, statek44, pudlo, trafienie, celownik);
		wypelnienie_pc(g2s1, g2s2, g2s3, g2s4);

		printf("s1 = x%d y%d\n", g2s1.p[0], g2s1.p[1]);

		printf("s2 p = x%d y%d\n", g2s2.p[0], g2s2.p[1]);
		printf("s2 k = x%d y%d\n", g2s2.k[0], g2s2.k[1]);

		printf("s3 p = x%d y%d\n", g2s3.p[0], g2s3.p[1]);
		printf("s3 s = x%d y%d\n", g2s3.s[0], g2s3.s[1]);
		printf("s3 k = x%d y%d\n", g2s3.k[0], g2s3.k[1]);

		printf("s4 p = x%d y%d\n", g2s4.p[0], g2s4.p[1]);
		printf("s4 s = x%d y%d\n", g2s4.s[0], g2s4.s[1]);
		printf("s4 s1 = x%d y%d\n", g2s4.s1[0], g2s4.s1[1]);
		printf("s4 p = x%d y%d\n", g2s4.k[0], g2s4.k[1]);
	}
	zamiana_ruchu(&font8);
	auto begin = std::chrono::high_resolution_clock::now();
	printf("glowna pentla\n");
	while (pentla_gra)
	{
		//gracz nr 1
		if (punktyp1 < 6 && punktyp2 < 6)
		{
			celowanie(g1s1, g1s2, g1s3, g1s4, &event_queue, &kx, &ky, font8, punktyp1, punktyp2, ekran, statek11, statek22, statek33, statek44, pudlo, trafienie, celownik, historiaxp1, historiayp1, historiatraf);
			prevp1 = punktyp1;
			historiaxp1.push_back(kx);
			historiayp1.push_back(ky);
			//tworzenie historii ruchow
			strzal(g2s1, g2s2, g2s3, g2s4, kx, ky, &punktyp1, &font8,&bladx,&blady,&traf, historiatraf);
			//jesli po strzale punktu sie nie zmienia to ostatni strzal byl pudlem czyli oznaczamy go zerem 
			if (prevp1 != punktyp1)
			{
				historiatraf.push_back(1);
			}
			else
			{
				historiatraf.push_back(0);
			}
		}
		else
		{
			pentla_gra = false;
			break;
		}

		if (komputer == 0)
		{
			//jesli gramy z graczem to wyswietlamy zmiane ruchu 
			//jesli ostatni strzal bym zwycieskim to nie wyswietlamy zmiany ruchu
			if (punktyp1 < 6 && punktyp2 < 6)
			{
				zamiana_ruchu(&font8);
				//system("cls");
				cout << "punkty:" << endl;
				cout << "Gracz 1 :" << punktyp1 << endl;
				cout << "Gracz 2 :" << punktyp2 << endl;
			}
		}

		//gracz nr 2 analogiczne dzialanie do gracza nr1
		if (komputer == 0)
		{
			if (punktyp1 < 6 && punktyp2 < 6)
			{
				celowanie(g2s1, g2s2, g2s3, g2s4, &event_queue, &kx, &ky, font8, punktyp1, punktyp2, ekran, statek11, statek22, statek33, statek44, pudlo, trafienie, celownik, historiaxp1, historiayp1, historiatraf);
				prevp2 = punktyp2;
				historiaxp2.push_back(kx);
				historiayp2.push_back(ky);
				strzal(g1s1, g1s2, g1s3, g1s4, kx, ky, &punktyp2, &font8, &bladx, &blady, &traf, historiatraf);
				if (prevp2 != punktyp2)
				{
					historiatraf.push_back(1);
				}
				else
				{
					historiatraf.push_back(0);
				}
			}
			else
			{
				pentla_gra = false;
				break;
			}
			if (punktyp1 < 6 && punktyp2 < 6)
			{
				zamiana_ruchu(&font8);
				//system("cls");
				cout << "punkty:" << endl;
				cout << "Gracz 1 :" << punktyp1 << endl;
				cout << "Gracz 2 :" << punktyp2 << endl;
			};
		}
		else
		{
			if (punktyp1 < 6 && punktyp2 < 6)
			{
				strzal_pc(font8);
				
				if (komputer == 2)
				{
					//komputer == 2 to iteligenty 
					//komputer == 1 to nie inteligenty
					pc_strzal(&kx, &ky, g1s1, g1s2, g1s3, g1s4, &tx, &ty, &traf, historiaxp2, historiayp2);
				}
				else
				{
					kx = rand() % 5;
					ky = rand() % 5;
				}
				historiaxp2.push_back(kx);
				historiayp2.push_back(ky);
				strzal(g1s1, g1s2, g1s3, g1s4, kx, ky, &punktyp2, &font8,&tx,&ty, &traf, historiatraf);
			}
			else
			{
				pentla_gra = false;
				break;
			}
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

	//wyswietlenie w konsoli informacji o rozgrywce
	koniec_gry(&font8, punktyp1, punktyp2, &event_queue);
	if (punktyp1 > 10) cout << "Wygral gracz nr 1";
	else cout << "Wygral gracz nr 2" << endl;
	//czas rozgrywki
	printf("Czas rozgrywki: %.3f s.\n", elapsed.count() * 1e-9);
	cout << endl;
	cout << "Historia Gracza nr 1:" << endl;
	y1 = historiayp1.begin();
	for (x1 = historiaxp1.begin(); x1 != historiaxp1.end(); ++x1)
	{
		if (y1 != historiayp1.end())
		{
			cout << "(" << *x1 << "," << *y1 << ")" << " ,";
		}
		y1++;
	}

	cout << endl;
	cout << "Historia Gracza nr 2:" << endl;
	y1 = historiayp2.begin();
	for (x1 = historiaxp2.begin(); x1 != historiaxp2.end(); ++x1)
	{
		if (y1 != historiayp2.end())
		{
			cout << "(" << *x1 << "," << *y1 << ")" << " ,";
		}
		y1++;
	}


	return 0;
}

