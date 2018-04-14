//Kamil Czajka
#include <iostream>
using namespace std;

struct Connection{
	char destinationA;
	char destinationB;
	char destinationC;
	int destinationValue;
	Connection* next;

	Connection(char a, char b, char c, int v) : destinationA(a), destinationB(b), destinationC(c), destinationValue(v){
		next = NULL;
	} 

	~Connection(){}
};

struct Bead{
	int value;
	Bead* next;
	Connection* first;
	
	Bead(int v) : value(v){
		next = NULL;
		first = NULL;
	}

    Connection* search(char a, char b, char c, int v){
		Connection* walk = first;

		while (walk != NULL){
			if (walk->destinationA == a && walk->destinationB == b && walk->destinationC == c && walk->destinationValue == v){
				return walk;
			}

			walk = walk->next;
		}

		return NULL;
	}

	void print(){
		Connection* walk = first;

		while (walk != NULL){
			cout << " " << walk->destinationA << walk->destinationB << walk->destinationC << " " << walk->destinationValue;
			walk = walk->next;
		}
	}

	~Bead(){
		Connection* walk = first;
		Connection* p;

		while ((walk = first)){
			p = walk;
			first = walk->next;
			delete p;
		}
	}
};

struct Twine{
	char valueA;
	char valueB;
	char valueC;
	Twine* next;
	Bead* first;

	Twine(char a, char b, char c) : valueA(a), valueB(b), valueC(c){
		next = NULL;
		first = NULL;
	}

	bool isLowerThan(Bead* first, Bead* second){
		return first->value < second->value;
	}

	bool isGreaterThan(Bead* first, Bead* second){
		return first->value > second->value;
	}

	bool isEqual(Bead* first, Bead* second){
		return first->value == second->value;
	}

	Bead* search(int v){
		Bead* walk = first;
		
		while (walk != NULL){
			if (walk->value == v){
				return walk;
			}
			
			walk = walk->next;
		}
		
		return NULL;
	}
	
	void print(){
		Bead* walk = first;

		while (walk != NULL){
			cout << endl << walk->value;
			walk->print();
			walk = walk->next;
		}
	}

	~Twine(){
		Bead* walk = first;
		Bead* p;

		while ((walk = first)){
			p = walk;
			first = walk->next;
			delete p;
		}
	}
};

struct Warehouse{
	Twine* first;

	Warehouse(){
		first = NULL;
	}

	void control(){
		char input, a, b, c, a2, b2, c2;
		int v, v2;
		bool d = false;

		while (true){
			cin >> input;
			if (input == 'S'){
				cin >> a >> b >> c;
				addTwine(a, b, c);
			}
			if (input == 'B'){
				cin >> v >> a >> b >> c;
				addBead(v, a, b, c);
			}
			if (input == 'L'){
				cin >> v >> a >> b >> c >> v2 >> a2 >> b2 >> c2;
				addConnection(v, a, b, c, v2, a2, b2, c2);
			}
			if (input == 'U'){
				cin >> v >> a >> b >> c >> v2 >> a2 >> b2 >> c2;
				deleteConnection(v, a, b, c, v2, a2, b2, c2, d);
			}
			if (input == 'D'){
				cin >> v >> a >> b >> c;
				deleteBead(v, a, b, c);
			}
			if (input == 'M'){
				cin >> v >> a >> b >> c >> a2 >> b2 >> c2;
				moveBead(v, a, b, c, a2, b2, c2);
			}
			if (input == 'R'){
				cin >> a >> b >> c;
				deleteTwine(a, b, c);
			}
			if (input == 'P'){
				print();
			}
			if (input == 'F'){
				cout << endl;
				break;
			}
		}
	}

	void addTwine(char a, char b, char c){
		Twine* walk = first;
		Twine* walkAfter = NULL;

		Twine* newest = new Twine(a, b, c);
		if (first == NULL){
			first = newest;
			return;
		}
		else{
			if (first->next == NULL){		// lista jednoelementowa
				if (isEqual(newest, first)){
					delete newest;
					return;
				}
				else{
					if (isLowerThan(newest, first)){
						newest->next = first;
						first = newest;
					}
					else{
						first->next = newest;
					}
					return;
				}
			}
			else{
				while (walk != NULL){	// znajdowanie miejsca dla sznurka
					if (walkAfter == NULL){
						if (isEqual(newest, first)){
							delete newest;
							return;
						}
						else{
							if (isLowerThan(newest, first)){
								newest->next = first;
								first = newest;
								return;
							}
						}
					}
					else{
						if (isEqual(newest, walkAfter) || isEqual(newest, walk)){
							delete newest;
							return;
						}
						else{
							if (isGreaterThan(newest, walkAfter) && isLowerThan(newest, walk)){
								walkAfter->next = newest;
								newest->next = walk;
								return;
							}
						}
					}

					walkAfter = walk;
					walk = walk->next;
				}
			}
		}

		walkAfter->next = newest; 	// sznurek na końcu
	}

	void deleteTwine(char a, char b, char c){
		Twine* s1 = search(a, b, c);

		if (s1 == NULL){
			return;
		}

		Bead* walk = s1->first;
	
		while ((walk = s1->first)){
			deleteBead(walk->value, a, b, c);
		}

		Twine* walkS = first;
		Twine* walkAfterS = NULL;

		while (walkS != NULL){
			if (isEqual(walkS->valueA, walkS->valueB, walkS->valueC, a, b, c)){
				if (walkAfterS == NULL){
					first = walkS->next;
					delete walkS;
					return;
				}
				else{
					if (walkS->next == NULL){
						walkAfterS->next = NULL;
						delete walkS;
						return;
					}
					else{
						walkAfterS->next = walkS->next;
						delete walkS;
						return;
					}
				}
			}

			walkAfterS = walkS;
			walkS = walkS->next;
		}
	}

	void addBead(int v, char a, char b, char c){
		Twine* twine = search(a, b, c);

		if (twine == NULL){
			return;
		}

		Bead* walk = twine->first;
		Bead* walkAfter = NULL;

		Bead* newest = new Bead(v);
		if (twine->first == NULL){
			twine->first = newest;
			return;
		}
		else{
			if (twine->first->next == NULL){
				if (twine->isEqual(newest, twine->first)){
					delete newest;
					return;
				}
				else{
					if (twine->isLowerThan(newest, twine->first)){
						newest->next = twine->first;
						twine->first = newest;
					}
					else{
						twine->first->next = newest;
					}
					return;
				}
			}
			else{
				while (walk != NULL){	
					if (walkAfter == NULL){
						if (twine->isEqual(newest, twine->first)){
							delete newest;
							return;
						}
						else{
							if (twine->isLowerThan(newest, twine->first)){
								newest->next = twine->first;
								twine->first = newest;
								return;
							}
						}
					}
					else{
						if (twine->isEqual(newest, walkAfter) || twine->isEqual(newest, walk)){
							delete newest;
							return;
						}
						else{
							if (twine->isGreaterThan(newest, walkAfter) && twine->isLowerThan(newest, walk)){
								walkAfter->next = newest;
								newest->next = walk;
								return;
							}
						}
					}

					walkAfter = walk;
					walk = walk->next;
				}
			}
		}

		walkAfter->next = newest;
	}

	void deleteBead(int v, char a, char b, char c){
		Twine* s1 = search(a, b, c);

		if (s1 == NULL){
			return;
		}

		if (s1->first == NULL){
			return;
		}

		Bead* walk = s1->first;
		Bead* walkAfter = NULL;

		while (walk != NULL){
			if (walk->value == v){
				if (walkAfter == NULL){
					s1->first = walk->next;
					delete walk;
					break;
				}
				else{
					if (walk->next == NULL){
						walkAfter->next = NULL;
						delete walk;
						break;
					}
					else{
						walkAfter->next = walk->next;
						delete walk;
						break;
					}
				}
			}

			walkAfter = walk;
			walk = walk->next;
		}

		Twine* walkS = first;
		Bead* walkK;
		bool d = false;

		while (walkS != NULL){
			walkK = walkS->first;
			while (walkK != NULL){
				deleteConnection(walkK->value, walkS->valueA, walkS->valueB, walkS->valueC, v, a, b, c, d);
				walkK = walkK->next;
			}

			walkS = walkS->next;
		}
	}

	void moveBead(int v, char a, char b, char c, char a2, char b2, char c2){
		Twine* s1 = search(a, b, c);
		Twine* s2 = search(a2, b2, c2);

		if (s1 == NULL || s2 == NULL){
			return;
		}

		Bead* walkS2 = s2->first;

		while (walkS2 != NULL){
			if (walkS2->value == v){
				return;
			}

			walkS2 = walkS2->next;
		}

		Bead* walk = s1->first;
		Bead* walkAfter = NULL;

		while (walk != NULL){
			if (walk->value == v){
				if (walkAfter == NULL){
					s1->first = walk->next;
					break;
				}
				else{
					if (walk->next == NULL){
						walkAfter->next = NULL;
						break;
					}
					else{
						walkAfter->next = walk->next;
						break;
					}
				}
			}

			walkAfter = walk;
			walk = walk->next;
		}

		if (walk == NULL){
			return;
		}

		walk->next = NULL;
		Bead* walk2 = s2->first;
		Bead* walkAfter2 = NULL;
		bool isMake = false;

		if (walk2 == NULL){
			s2->first = walk;
		}
		else{
			while (walk2 != NULL){
				if (walkAfter2 == NULL){
					if (walk->value < walk2->value){
						walk->next = walk2;
						s2->first = walk;
						isMake = true;
						break;
					}
				}
				else{
					if (walkAfter2->value < walk->value && walk->value < walk2->value){
						walkAfter2->next = walk;
						walk->next = walk2;
						isMake = true;
						break;
					}
				}

				walkAfter2 = walk2;
				walk2 = walk2->next;
			}

			if (isMake == false){
				walkAfter2->next = walk;
			}
		}
	}

	void addConnection(int v, char a, char b, char c, int v2, char a2, char b2, char c2){
		Twine* s1 = search(a, b, c);
		Twine* s2 = search(a2, b2, c2);

		if (s1 == NULL || s2 == NULL){
			return;
		}

		Bead* k1 = s1->search(v);
		Bead* k2 = s2->search(v2);

		if (k1 == NULL || k2 == NULL){
			return;
		}

		Connection* newest = new Connection(a2, b2, c2, v2);
		Connection* walk = k1->first;
		Connection* walkAfter = NULL;

		if (walk == NULL){	//pusta
			k1->first = newest;
			return;
		}
		else{
			if (walk->next == NULL){	// jeden element
				if (isLowerThan(a2, b2, c2, k1->first->destinationA, k1->first->destinationB, k1->first->destinationC)){ // <
					newest->next = k1->first;
					k1->first = newest;
					return;
				}
				else{
					if (isEqual(a2, b2, c2, k1->first->destinationA, k1->first->destinationB, k1->first->destinationC)){ // ==
						if (v2 < k1->first->destinationValue){	// == <
							newest->next = k1->first;
							k1->first = newest;
							return;
						}
						else{
							if (v2 == k1->first->destinationValue){ // == ==
								delete newest;
								return;
							}
							else{
								k1->first->next = newest;	// == >
								return;
							}
						}
					}
					else{	// >
						k1->first->next = newest;
						return;
					}
				}
			}
			else{	// wiecej niż jeden element
				if (isLowerThan(a2, b2, c2, walk->destinationA, walk->destinationB, walk->destinationC)){	// na poczatek
					newest->next = walk;
					k1->first = newest;
					return;
				}
				else{
					if (isEqual(a2, b2, c2, walk->destinationA, walk->destinationB, walk->destinationC) && v2 < walk->destinationValue){
						newest->next = walk;
						k1->first = newest;
						return;
					}
				}


				walkAfter = walk;
				walk = walk->next;

				while (walk != NULL){
					if (isEqual(walkAfter->destinationA, walkAfter->destinationB, walkAfter->destinationC, walk->destinationA, walk->destinationB, walk->destinationC)){
						if (isEqual(a2, b2, c2, walkAfter->destinationA, walkAfter->destinationB, walkAfter->destinationC)){	// == ==
							if (v2 == walkAfter->destinationValue || v2 == walk->destinationValue){
								delete newest;
								return;
							}
							else{
								if (v2 > walkAfter->destinationValue && v2 < walk->destinationValue){
									walkAfter->next = newest;
									newest->next = walk;
									return;
								}
							}
						}
					}
					else{
						if (isEqual(a2, b2, c2, walkAfter->destinationA, walkAfter->destinationB, walkAfter->destinationC)){ // == <
							if (v2 == walkAfter->destinationValue){	// == < ==
								delete newest;
								return;
							}
							else{	// == < 
								walkAfter->next = newest;
								newest->next = walk;
								return;
							}
						}
						else{
							if (isLowerThan(a2, b2, c2, walk->destinationA, walk->destinationB, walk->destinationC)){	// > <
								walkAfter->next = newest;
								newest->next = walk;
								return;
							}
							else{
								if (isEqual(a2, b2, c2, walk->destinationA, walk->destinationB, walk->destinationC)){	// < ==
									if (v2 == walk->destinationValue){	// < == ==
										delete newest;
										return;
									}
									else{	// < == <
										if (v2 < walk->destinationValue){
											walkAfter->next = newest;
											newest->next = walk;
											return;
										}
									}
								}
							}
						}
					}
				
					walkAfter = walk;
					walk = walk->next;
				}

				walkAfter->next = newest;	// na koncu
			}
		}
	}

	void deleteConnection(int v, char a, char b, char c, int v2, char a2, char b2, char c2, bool& d){
		Twine* s1 = search(a, b, c);
		
		if (s1 == NULL){
			return;
		}

		Bead* k1 = s1->search(v);

		if (k1 == NULL){
			return;
		}

		if (k1->first == NULL){
			return;
		}

		Connection* walk = k1->first;
		Connection* walkAfter = NULL;

		while (walk != NULL){
			if (isEqual(walk->destinationA, walk->destinationB, walk->destinationC, a2, b2, c2) && walk->destinationValue == v2){
				if (walkAfter == NULL){	// na poczatku
					k1->first = walk->next;
					delete walk;
					d = true;
					return;
				}
				else{
					if (walk->next == NULL){ // na koncu
						walkAfter->next = NULL;
						delete walk;
						d = true;
						return;
					}
					else{
						walkAfter->next = walk->next;
						delete walk;
						d = true;
						return;
					}
				}
			}

			walkAfter = walk;
			walk = walk->next;
		}
	}


	bool isEqual(Twine* first, Twine* second){		// a == b
		return (first->valueA == second->valueA) && (first->valueB == second->valueB) && (first->valueC == second->valueC);
	}

	bool isEqual(char a1, char b1, char c1, char a2, char b2, char c2){
		return (a1 == a2) && (b1 == b2) && (c1 == c2);
	}

	bool isLowerThan(Twine* first, Twine* second){		// a < b
		if (first->valueA < second->valueA){
			return true;
		}
		if (first->valueA == second->valueA && first->valueB < second->valueB){
			return true;
		}
		if (first->valueA == second->valueA && first->valueB == second->valueB && first->valueC < second->valueC){
			return true;
		}
		
		return false;
	}

	bool isLowerThan(char a1, char b1, char c1, char a2, char b2, char c2){
		if (a1 < a2){
			return true;
		}
		if (a1 == a2 && b1 < b2){
			return true;
		}
		if (a1 == a2 && b1 == b2 && c1 < c2){
			return true;
		}

		return false;
	}

	bool isGreaterThan(Twine* first, Twine* second){		// a > b
		if (first->valueA > second->valueA){
			return true;
		}
		if (first->valueA == second->valueA && first->valueB > second->valueB){
			return true;
		}
		if (first->valueA == second->valueA && first->valueB == second->valueB && first->valueC > second->valueC){
			return true;
		}
	
		return false;
	}

	bool isGreaterThan(char a1, char b1, char c1, char a2, char b2, char c2){
		if (a1 > a2){
			return true;
		}
		if (a1 == a2 && b1 > b2){
			return true;
		}
		if (a1 == a2 && b1 == b2 && c1 > c2){
			return true;
		}

		return false;
	}

	Twine* search(char a, char b, char c){
		Twine* p = new Twine(a, b, c);
		Twine* walk = first;

		while (walk != NULL){
			if (isEqual(walk, p)){
				delete p;
				return walk;
			}

			walk = walk->next;
		}

		delete p;
		return NULL;
	}

	void print(){
		Twine* walk = first;
		static bool isMade = false;

		if (walk == NULL){
			cout << endl;
		}
		else{
			while (walk != NULL){
				if (isMade == true){
					cout << endl;
				}
				cout << walk->valueA << walk->valueB << walk->valueC;
				walk->print();
				walk = walk->next;
				isMade = true;
			}
		}
	}

	~Warehouse(){
		Twine* walk = first;
		Twine* p;

		while ((walk = first)){
			p = walk;
			first = walk->next;
			delete p;
		}
	}
};

int main(){
	Warehouse* m = new Warehouse();
	m->control();
	delete m;
	return 0;
}
