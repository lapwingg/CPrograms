//Kamil Czajka
#include <stdio.h>
#include <stdlib.h>

struct Polozenie{
	int wspX;
	int wspY;
	int wspZ;
	char ident;
	struct Polozenie* next;
	struct Polozenie* prev;
};

void konstruktorPolozenie(struct Polozenie** p, int x, int y, int z, char i){
	(*p)->wspX = x;
	(*p)->wspY = y;
	(*p)->wspZ = z;
	(*p)->ident = i;
	(*p)->next = NULL;
	(*p)->prev = NULL;
}

void dodajElement(struct Polozenie** pierwsze, struct Polozenie** ostatnie, struct Polozenie** nowe){
	if (*pierwsze == NULL){
		*pierwsze = *nowe;
		*ostatnie = *pierwsze;
	}
	else{
		(*ostatnie)->next = *nowe;
		(*nowe)->prev = *ostatnie;
		*ostatnie = *nowe;
	}
}

void usunListe(struct Polozenie** pierwsze){
	struct Polozenie* tmp;

	while (*pierwsze != NULL){
		tmp = *pierwsze;
		*pierwsze = (*pierwsze)->next;
		free(tmp);
	}
}

struct Plansza{
	int promien;
	int wysokosc;
	int srodekX;
	int srodekY;
	struct Polozenie* aktualnyCel;
	int odlegloscOdCelu;
};

void konstruktorPlansza(struct Plansza** p, int r, int h){
	(*p)->promien = r;
	(*p)->wysokosc = h;
	(*p)->srodekX = r;
	(*p)->srodekY = r;
	(*p)->aktualnyCel = (struct Polozenie*)(malloc(sizeof(struct Polozenie)));
	konstruktorPolozenie(&((*p)->aktualnyCel), -1, -1, -1, ' ');
	(*p)->odlegloscOdCelu = -1;
}

int poleNalezyDoPlanszy(struct Plansza** p, int x, int y, int z){
	if (z >= 0 && z <= (*p)->wysokosc){	
		if (x * x + y * y <= ((*p)->promien) * (*p)->promien){
			return 1;
		}
	}

	return 0;
}

struct Regula{
		int zmianaX;
		int zmianaY;
		int zmianaZ;
};

void konstruktorRegula(struct Regula* r){
	r[0].zmianaX = 0; r[0].zmianaY = -1; r[0].zmianaZ = 0;
	r[1].zmianaX = -1; r[1].zmianaY = 0; r[1].zmianaZ = 0;
	r[2].zmianaX = 0; r[2].zmianaY = 1; r[2].zmianaZ = 0;
	r[3].zmianaX = 1; r[3].zmianaY = 0; r[3].zmianaZ = 0;
	r[4].zmianaX = 0; r[4].zmianaY = 0; r[4].zmianaZ = -1;
	r[5].zmianaX = 0; r[5].zmianaY = 0; r[5].zmianaZ = 1;
}

struct Manager{
	struct Polozenie* waz;
	struct Polozenie* wazKoniec;
	int dlugoscWeza;
	struct Plansza* plansza;
	char identPrzeszkody;
	struct Polozenie* pokarm;
	struct Polozenie* pokarmOstatni;
	int ilePokarmu;
	struct Polozenie* przeszkoda;
	struct Polozenie* przeszkodaOstatnia;
	struct Regula regula[6];
};

void konstruktor(struct Manager** m, char i){
	int r, h, x0, y0, z0, n;
	char ident, tmp, tmp2, tmp3;

	(*m)->identPrzeszkody = i;
	konstruktorRegula((*m)->regula);
	
	scanf("%d %d", &r, &h);
	(*m)->plansza = (struct Plansza*)(malloc(sizeof(struct Plansza)));
	konstruktorPlansza(&((*m)->plansza), r, h);
	
	(*m)->dlugoscWeza = 2;
	int k = 0;
	while (k < (*m)->dlugoscWeza){
		scanf("%d %d %d", &x0, &y0, &z0);
		struct Polozenie* pol = (struct Polozenie*)(malloc(sizeof(struct Polozenie)));
		konstruktorPolozenie(&pol, x0, y0, z0, '^');
		dodajElement(&((*m)->waz), &((*m)->wazKoniec), &pol);
		k++;
	}
	
	(*m)->ilePokarmu = 0;
	scanf("%d", &n);
	k = 0;
	while(k < n){
		while (1){
			scanf("%c", &tmp);
			if (tmp == '@' || tmp == '$' || tmp == '%' || tmp == '*' || tmp == (*m)->identPrzeszkody){
				ident = tmp;
				break;
			}
		}
		scanf("%c%d%c%d%c%d", &tmp, &x0, &tmp, &y0, &tmp, &z0);
		if ((*m)->identPrzeszkody == ident){
			struct Polozenie* pol = (struct Polozenie*)(malloc(sizeof(struct Polozenie)));
			konstruktorPolozenie(&pol, x0, y0, z0, (*m)->identPrzeszkody);
			dodajElement(&((*m)->przeszkoda), &((*m)->przeszkodaOstatnia), &pol);
		}
		else{
			struct Polozenie* pol = (struct Polozenie*)(malloc(sizeof(struct Polozenie)));
			konstruktorPolozenie(&pol, x0, y0, z0, ident);
			dodajElement(&((*m)->pokarm), &((*m)->pokarmOstatni), &pol);
			((*m)->ilePokarmu)++;
		}
		k++;
	}
}

int odlegloscEuklidesowska(struct Polozenie** pierwsze, struct Polozenie** drugie){
	return (((*pierwsze)->wspX - (*drugie)->wspX) * ((*pierwsze)->wspX - (*drugie)->wspX)) + (((*pierwsze)->wspY - (*drugie)->wspY) * ((*pierwsze)->wspY - (*drugie)->wspY)) + (((*pierwsze)->wspZ - (*drugie)->wspZ) * ((*pierwsze)->wspZ - (*drugie)->wspZ));
}

int odlegloscEuklidesowskaSkalary(int x0, int y0, int z0, int x1, int y1, int z1){
	return ((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1) + (z0 - z1) * (z0 - z1));
}

void stanRozgrywki(struct Polozenie** walkWaz, struct Polozenie** walkPrzeszkoda, struct Polozenie** walkPokarm){
		struct Polozenie* tmp = *walkWaz;
		int a = 1;
		
		while (tmp != NULL){
			if (a == 1){
				printf("^:%d;%d;%d", tmp->wspX, tmp->wspY, tmp->wspZ);
				a = 0;
			}
			else{
				printf("|:%d;%d;%d", tmp->wspX, tmp->wspY, tmp->wspZ);
			}

			tmp = tmp->next;
		}
		printf("\n");

		tmp = *walkPrzeszkoda;
		while (tmp != NULL){
			printf("%c:%d;%d;%d", tmp->ident, tmp->wspX, tmp->wspY, tmp->wspZ);

			tmp = tmp->next;
		}
		printf("\n");
	
		tmp = *walkPokarm;
		if (tmp != NULL){
			while (tmp != NULL){
				printf("%c:%d;%d;%d", tmp->ident, tmp->wspX, tmp->wspY, tmp->wspZ);
		
				tmp = tmp->next;
			}
			printf("\n");
		}
}

void aktualizujWeza(struct Polozenie** waz, int x, int y, int z){
	struct Polozenie* walk = *waz;

	while (walk->prev != NULL){
		walk->wspX = walk->prev->wspX;
		walk->wspY = walk->prev->wspY;
		walk->wspZ = walk->prev->wspZ;
		walk = walk->prev;
	}

	walk->wspX = x;
	walk->wspY = y;
	walk->wspZ = z;
}

void zjedzPokarm(struct Polozenie** waz, struct Polozenie** wazKoniec, int x, int y, int z, char i){
	int n;
	int zmianaX, zmianaY, zmianaZ;

	if (i == '@'){
		n = 0;
	}
	if (i == '%'){
		n = 1;
	}
	if (i == '$'){
		n = 2;
	}
	if (i == '*'){
		n = 3;
	}

	struct Polozenie* pol = (struct Polozenie*)(malloc(sizeof(struct Polozenie)));
	konstruktorPolozenie(&pol, x, y, z, '^');
	pol->next = *waz;
	(*waz)->prev = pol;
	*waz = pol;

	zmianaX = -1 * ((*waz)->wspX - (*waz)->next->wspX);
	zmianaY = -1 * ((*waz)->wspY - (*waz)->next->wspY);
	zmianaZ = -1 * ((*waz)->wspZ - (*waz)->next->wspZ);

	int k = 0;
	while (k < n){
		struct Polozenie* nowe = (struct Polozenie*)(malloc(sizeof(struct Polozenie)));
		konstruktorPolozenie(&nowe, (*wazKoniec)->wspX + zmianaX, (*wazKoniec)->wspY + zmianaY, (*wazKoniec)->wspZ + zmianaZ, '^');
		dodajElement(waz, wazKoniec, &nowe);
		k++;
	}
} 

void usunPokarm(struct Polozenie** pokarm, struct Polozenie** ostatni, int x, int y, int z){
	struct Polozenie* walk = *pokarm;

	while (walk != NULL){
		if (walk->wspX == x && walk->wspY == y && walk->wspZ == z){
			if (walk->prev == NULL){
				if (walk->next == NULL){
					*pokarm = NULL;
					*ostatni = NULL;
					free(walk);
					return;
				}
				else{
					walk->next->prev = NULL;
					*pokarm = walk->next;
					free(walk);
					return;
				}
			}
			else{
				if (walk->next == NULL){
					walk->prev->next = NULL;
					*ostatni = walk->prev;
					free(walk);
					return;
				}
				else{
					walk->next->prev = walk->prev;
					walk->prev->next = walk->next;
					free(walk);
					return;
				}
			}
		}

		walk = walk->next;
	}
}

void rozgrywka(struct Manager** m){
	int akt = 1;
	while ((*m)->ilePokarmu > 0){
		stanRozgrywki(&((*m)->waz), &((*m)->przeszkoda), &((*m)->pokarm));

		if ((*m)->plansza->odlegloscOdCelu == -1){	// poszukiwanie celu
			int celX, celY, celZ; char celI;
			struct Polozenie* walk = (*m)->pokarm;
			int minOdl = -1, x;
			
	//		printf("Wybieranie celu! %d%d%d\n", (*m)->waz->wspX, (*m)->waz->wspY, (*m)->waz->wspZ);
			while (walk != NULL){
				x = odlegloscEuklidesowska(&walk, &((*m)->waz));
			//	printf("%d%d%d %d\n", walk->wspX, walk->wspY, walk->wspZ, x);
				if (minOdl == -1){
					minOdl = x;
					celX = walk->wspX;
					celY = walk->wspY;
					celZ = walk->wspZ;
					celI = walk->ident;
				}
				else{
					if (x <= minOdl){
						minOdl = x;
						celX = walk->wspX;
						celY = walk->wspY;
						celZ = walk->wspZ;
						celI = walk->ident;
					}
				}

				walk = walk->next;
	//			printf("aktualnyWybór = %d%d%d %d\n", celX, celY, celZ, minOdl);
			}
			(*m)->plansza->aktualnyCel->wspX = celX;
			(*m)->plansza->aktualnyCel->wspY = celY;
			(*m)->plansza->aktualnyCel->wspZ = celZ;
			(*m)->plansza->aktualnyCel->ident = celI;
			(*m)->plansza->odlegloscOdCelu = minOdl;
		}
		
				// zmiana położenie węża
		int i = 0, x, y, z, odl;
		int jestPrzeszkoda = 0, ogon = 0;
		struct Polozenie* walk;
	//	printf("Zmiana polozenia\n");
		while (i < 6){
			x = (*m)->waz->wspX + (*m)->regula[i].zmianaX;
			y = (*m)->waz->wspY + (*m)->regula[i].zmianaY;
			z = (*m)->waz->wspZ + (*m)->regula[i].zmianaZ;
	//		printf("czy %d%d%d?\n", x, y, z);
			odl = odlegloscEuklidesowskaSkalary(x, y, z, (*m)->plansza->aktualnyCel->wspX, (*m)->plansza->aktualnyCel->wspY, (*m)->plansza->aktualnyCel->wspZ);
	//		printf("%d\n", odl);
			if (odl < (*m)->plansza->odlegloscOdCelu){ // czy nie ma przeszkod i ogona?
				if (odl == 0){
	//				printf("Zjadlem pokarm z %d%d%d\n", x, y, z);
					zjedzPokarm(&((*m)->waz), &((*m)->wazKoniec), x, y, z, (*m)->plansza->aktualnyCel->ident);
					usunPokarm(&((*m)->pokarm), &((*m)->pokarmOstatni), x, y, z);
					((*m)->ilePokarmu)--;
					(*m)->plansza->odlegloscOdCelu = -1;
					break;
				}

				walk = (*m)->przeszkoda;
				jestPrzeszkoda = 0;				
				while (walk != NULL){
	//				printf("%d%d%d %d%d%d\n", walk->wspX, walk->wspY, walk->wspZ, x, y, z);
					if (walk->wspX == x && walk->wspY == y && walk->wspZ == z){
						jestPrzeszkoda = 1;
						break;
					}

					walk = walk->next;
				}
	//			printf("przeszkoda = %d\n", jestPrzeszkoda);
				ogon = 0;
				walk = (*m)->waz->next;
				while (walk != NULL){
	//				printf("%d%d%d %d%d%d\n", walk->wspX, walk->wspY, walk->wspZ, x, y, z);
					if (walk->wspX == x && walk->wspY == y && walk->wspZ == z){
						ogon = 1;
						break;
					}

					walk = walk->next;
				}
	//			printf("ogon = %d\n", ogon);
	//			printf("plansza = %d\n", poleNalezyDoPlanszy(&((*m)->plansza), x, y, z) == 0);
				if (jestPrzeszkoda || ogon || poleNalezyDoPlanszy(&((*m)->plansza), x, y, z) == 0){
	//				printf("Tryb Przeszkody\n");
					int k = 0, wX, wY, wZ, od, pr = 1;
					int min[2][4];
					min[0][0] = -1; 
					min[1][0] = -1; 

					while (k < 6){
						wX = (*m)->waz->wspX + (*m)->regula[k].zmianaX;
						wY = (*m)->waz->wspY + (*m)->regula[k].zmianaY;
						wZ = (*m)->waz->wspZ + (*m)->regula[k].zmianaZ;
	//					printf("pkt = %d%d%d\n", wX, wY, wZ);
						if ((wX == x && wY == y && wZ == z) == 0){	
							if (poleNalezyDoPlanszy(&((*m)->plansza), wX, wY, wZ)){
								od = odlegloscEuklidesowskaSkalary((*m)->plansza->aktualnyCel->wspX, (*m)->plansza->aktualnyCel->wspY, (*m)->plansza->aktualnyCel->wspZ, wX, wY, wZ);
	//							printf("odl = %d\n", od);
								if (min[0][0] == -1){
									min[0][0] = od;
									min[0][1] = wX;
									min[0][2] = wY;
									min[0][3] = wZ;
								}
								else{
									if (od < min[0][0]){
										min[1][0] = min[0][0];
										min[1][1] = min[0][1];
										min[1][2] = min[0][2];
										min[1][3] = min[0][3];
										min[0][0] = od;
										min[0][1] = wX;
										min[0][2] = wY;
										min[0][3] = wZ;
									}
									else{
										if (od == min[0][0]){
											if (min[1][0] == -1){
												min[1][0] = od;
												min[1][1] = wX;
												min[1][2] = wY;
												min[1][3] = wZ;
											}
											else{
												if (od < min[1][0]){
													min[1][0] = od;
													min[1][1] = wX;
													min[1][2] = wY;
													min[1][3] = wZ;
												}
											}
										}
										else{
											if (min[1][0] == -1){
												min[1][0] = od;
												min[1][1] = wX;
												min[1][2] = wY;
												min[1][3] = wZ;
											}
											else{
												if (od < min[1][0]){
													min[1][0] = od;
													min[1][1] = wX;
													min[1][2] = wY;
													min[1][3] = wZ;
												}
											}
										}
									}
								}
							}
						}
						
	//					printf("%d %d%d%d\n%d %d%d%d\n\n", min[0][0], min[0][1], min[0][2], min[0][3], min[1][0], min[1][1], min[1][2], min[1][3] );
						k++;
					}

					k = 0;
					while (k < 2){
						//if (poleNalezyDoPlanszy(&((*m)->plansza), min[k][1], min[k][2], min[k][3])){
							pr = 1;
							walk = (*m)->przeszkoda;				
							while (walk != NULL){
	//							printf(" przeszkoda = %d%d%d pkt = %d%d%d\n", walk->wspX, walk->wspY, walk->wspZ, min[k][1], min[k][2], min[k][3]);
								if (walk->wspX == min[k][1] && walk->wspY == min[k][2] && walk->wspZ == min[k][3]){
									pr = 0;
									break;
								}

								walk = walk->next;
							}

							walk = (*m)->waz->next;
							while (walk != NULL){
	//							printf(" ogon = %d%d%d pkt = %d%d%d\n", walk->wspX, walk->wspY, walk->wspZ, min[k][1], min[k][2], min[k][3]);
								if (walk->wspX == min[k][1] && walk->wspY == min[k][2] && walk->wspZ == min[k][3]){
									pr = 0;
									break;
								}

								walk = walk->next;
							}

							walk = (*m)->pokarm;
							while (walk != NULL){
								if (walk->wspX == min[k][1] && walk->wspY == min[k][2] && walk->wspZ == min[k][3]){
									zjedzPokarm(&((*m)->waz), &((*m)->wazKoniec), min[k][1], min[k][2], min[k][3], walk->ident);
									usunPokarm(&walk, &((*m)->pokarmOstatni), min[k][1], min[k][2], min[k][3]);
									((*m)->ilePokarmu)--;
									(*m)->plansza->odlegloscOdCelu = -1;
									akt = 0;
									break;
								}

								walk = walk->next;
							}
						//}

						if (pr){
	//						printf("akt = %d%d%d\n", min[k][1], min[k][2], min[k][3]);
							aktualizujWeza(&((*m)->wazKoniec), min[k][1], min[k][2], min[k][3]);
							(*m)->plansza->odlegloscOdCelu = -1;						
							akt = 0;
							break;
						}
						
						k++;
					}

					if (akt == 0){
						akt = 1;
						break;
					}
				}
				else{
					aktualizujWeza(&((*m)->wazKoniec), x, y, z);
					(*m)->plansza->odlegloscOdCelu = odl;
					break;
				}
			}

			i++;
		}	
	}

	stanRozgrywki(&((*m)->waz), &((*m)->przeszkoda), &((*m)->pokarm));		
}

void destruktor(struct Manager** m){
	free((*m)->plansza->aktualnyCel);
	free((*m)->plansza);
	usunListe(&((*m)->waz));
	usunListe(&((*m)->przeszkoda));
	usunListe(&((*m)->pokarm));
}

int main(){
	char ident;
	int n;
	struct Manager* m = (struct Manager*)(malloc(sizeof(struct Manager)));

	scanf("%c%d", &ident, &n);
	while (n > 0){
		konstruktor(&m, ident);
		rozgrywka(&m);
		destruktor(&m);
		n--;
	}
	
	free(m);
	
	return 0;
}
