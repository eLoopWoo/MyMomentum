#include <Windows.h>
#include <ball.h>
ball* p1;
ball* p2;
ball* p3;
ball* arr[100];

void Elastic() {
	//m1*v1+m2*v2=m1*u1+m2*u2 
	//v2-v1 = -(u2-u1)
	bool x = true;
	while (x) {
		int g;
		int h;
		int id = 0;

		float a1 = 0;
		float a2 = 0;
		float b1 = 0;
		float b2 = 0;
		float c1 = 0;
		float c2 = 0;

		float delta = 0;
		float deltaX = 0;
		float deltaY = 0;

		float x = 0;
		float y = 0;
		for (h = 0; h < 3; h++) {
			for (g = 0; g < 3; g++) {
				if (g == h)
					continue;
				if (abs((*arr[g]).get_x() - (*arr[h]).get_x()) < 40) {
					if (abs((*arr[g]).get_y() - (*arr[h]).get_y()) < 40) { 
						printf("%F  arr\n%F  p1 before\n", (*arr[h]).get_velocity_x(), (*arr[h]).get_velocity_y());

						c1 = ((*arr[h]).get_mass() * (*arr[h]).get_velocity_x() + (*arr[g]).get_mass() * (*arr[g]).get_velocity_x());
						c2 = (*arr[g]).get_velocity_x() - (*arr[h]).get_velocity_x();
						a1 = (*arr[h]).get_mass();
						b1 = (*arr[g]).get_mass();
						a2 = 1;
						b2 = -1;
						delta = a1*b2 - a2*b1;
						deltaX = b2*c1 - b1*c2;
						deltaY = a1*c2 - a2*c1;
						x = (deltaX / delta);
						y = (deltaY / delta);
						(*arr[h]).set_velocity_x(x);
						(*arr[g]).set_velocity_x(y);

						c1 = ((*arr[h]).get_mass() * (*arr[h]).get_velocity_y() + (*arr[g]).get_mass() * (*arr[g]).get_velocity_y());
						c2 = (*arr[g]).get_velocity_y() - (*arr[h]).get_velocity_y();
						a1 = (*arr[h]).get_mass();
						b1 = (*arr[g]).get_mass();
						a2 = 1;
						b2 = -1;
						delta = a1*b2 - a2*b1;
						deltaX = b2*c1 - b1*c2;
						deltaY = a1*c2 - a2*c1;
						x = (deltaX / delta);
						y = (deltaY / delta);
						(*p1).set_velocity_y(x);
						(*arr[g]).set_velocity_y(y);
						Sleep(15);
					}
				}
			}
		}
	}
}

void nonElastic() {
	bool x = true;
	while (x) {
		int g;
		int id = 0;
		for (g = 0; g < 2; g++) {
			if (g == id)
				continue;
			printf("%F  arr\n %F  p1 before\n", (*p1).get_velocity_x(), (*arr[g]).get_velocity_y());

			if ((int)(*arr[g]).get_x() - (int)(*p1).get_x()  < 30) {
				if ((int)(*arr[g]).get_y() - (int)(*p1).get_y() < 30) {
					//non elastic
					//	(m1 * v1x + m2 * v2x)/(m1 + m2) =  Ux
					(*p1).set_velocity_x((((*arr[g]).get_mass() * (*arr[g]).get_velocity_x() + (*p1).get_mass() * (*p1).get_velocity_x()) / ((*arr[g]).get_mass() + (*p1).get_mass())));
					(*p1).set_velocity_y((((*arr[g]).get_mass() * (*arr[g]).get_velocity_y() + (*p1).get_mass() * (*p1).get_velocity_y()) / ((*arr[g]).get_mass() + (*p1).get_mass())));
					(*p2).set_velocity_x((*p1).get_velocity_x());
					(*p2).set_velocity_y((*p1).get_velocity_y());
					Sleep(1000);
				}
			}
		}
	}


}
	

void game() {
	while (true) {
		(*p1).setPos((*p1).get_x(), (*p1).get_y());
		(*p2).setPos((*p2).get_x(), (*p2).get_y());
		(*p3).setPos((*p3).get_x(), (*p3).get_y());
		(*p1).play();
		(*p2).play();
		(*p3).play();
		Sleep(10);
	}
}


int main() {

	sf::RenderWindow window(sf::VideoMode(640, 480), "Momentum ver 1.0");
	ball ball1(200,200,&window);
	ball ball2(300,200,&window);
	ball ball3(500, 350, &window);
	arr[0] = &ball1;
	arr[1] = &ball2;
	arr[2] = &ball3;
	ball1.set_mass(550);
	(ball1.getCircle()).setFillColor(sf::Color(255, 255, 0));
	(ball2.getCircle()).setFillColor(sf::Color(0, 255, 255));
	(ball3.getCircle()).setFillColor(sf::Color(255, 0, 255));
	ball2.set_mass(50);
	ball3.set_mass(300);
	ball1.set_velocity_x(3.5);
	ball3.set_velocity_x(1.5);
	ball2.set_velocity_y(2.5);

	p1 = &ball1;
	p2 = &ball2;
	p3 = &ball3;
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)game, NULL, NULL, NULL);
	//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)nonElastic, NULL, NULL, NULL);
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Elastic, NULL, NULL, NULL);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		ball1.print();
		ball2.print();
		ball3.print();
		window.display();
	}



	return 0;
}