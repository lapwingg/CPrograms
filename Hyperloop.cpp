//Kamil Czajka
#include <iostream>
using namespace std;

template <typename type>
class Elem{
	public:
		type value;
		int index;
		Elem* next;

	Elem(int i){
		index = i;
		next = NULL;
	}

	Elem(type v, int i){
		value = v;
		index = i;
		next = NULL;
	}		
};

template <typename type>
class Tunnel{
	public:
		Elem<type>* first; // wsk. na poczatek tunelu
		Elem<type>* tmp; // pomocnicze wskazanie dla op= 
        Tunnel<type>* next; // pokrewienstwo tunela z innym
		int length; // dlugosc = najwyzsza wartosc podana w przeladowaniu []
		bool wasVisited;
		bool start;  
	
		Tunnel(){
			first = NULL;
			tmp = NULL;
			next = NULL;	
			length = -1;
			wasVisited = false;
			start = false; 				    	 
		}
		
		~Tunnel(){
			Elem<type>* walk = first;
			Elem<type>* p;
			
			while (walk != NULL){
			    p = walk;
				walk = walk->next;
				delete p;
			}

			length = -1;
			wasVisited = false;
			start = false;
		}
		
		Tunnel<type>& operator>>(Tunnel<type>& t2){
            next = &t2;
           
            return t2;
		}
		
		Tunnel<type>& operator[](int index){
			Elem<type>* nowy = new Elem<type>(index);
			
			if (index > length){
				length = index;
			}

			if (first == NULL){
				first = nowy;
				tmp = first;				
				return *this;
			}
			else{
                if (first->index == nowy->index){
                	tmp = first;
					delete nowy;
				    return *this;
				}

				if (nowy->index < first->index){
					nowy->next = first;
					first = nowy;
					tmp = first;
				    return *this;
				}
				else{
					Elem<type>* walk = first->next;
					Elem<type>* walkAfter = first;

					while (walk != NULL){
						if (walk->index == nowy->index){							
						    tmp = walk;     
						    delete nowy;
						    return *this;
						}    

						if (walkAfter->index == nowy->index){
						    tmp = walkAfter;
						    delete nowy;
						    return *this;
                        }

						if (walkAfter->index < nowy->index && nowy->index < walk->index){
							walkAfter->next = nowy;
							nowy->next = walk;
							tmp = nowy;
							return *this;
						}

						walkAfter = walk;
						walk = walk->next;
					}

					walkAfter->next = nowy;
					tmp = nowy;
					return *this;
				}	
			}	

			return *this;
		}
		
		Tunnel<type>& operator=(type value){
			if (tmp != NULL){
				tmp->value = value;
			}

			return *this;
		}
		
		void tick(){           
           start = true;
           tickRecursive(NULL);
           start = false;      			
		}

		void tickRecursive(Elem<type>* p){
            if (wasVisited == true){  // powoli koncz
            	if (start == true){   // pelna loop
            	    if (p != NULL){
            	    	if (first != NULL){
            	    	    p->index = 0;
            	    	    p->next = first;
            	    	   	first = p;
                        }
            	    	else{
            	    	    p->index = 0;
            	    	    first = p;
            	    	}       	 
            	    }
            	}    	 
                else{    // niepelna = usun  
            	    if (p != NULL){
            	        delete p;
            	    }
            	}

            	return;                
            }    	         
            else{
			    Elem<type>* walk = first;
			    Elem<type>* walkAfter = NULL;
			    Elem<type>* move = NULL;
			    int i = 0;

			    while (i <= length){
				    if (walk != NULL && i == walk->index){
					    if (i < length){  // przesun
						    walk->index++;  
						    walkAfter = walk;
						    walk = walk->next;
					    }
					    else{ // lass
                    	    move = walk;
                    	    if (first->next == NULL){	 // 1 elem						 
		        		        first = NULL;
		        	        }	
					        else{
					        	walkAfter->next = NULL;
						    }  									
				        }
			        }

			  	    i++;	 
			    } 

            	if (p != NULL){   // na poczatek            		
                	if (first != NULL){
                    	p->index = 0;  
                	    p->next = first;
                	    first = p;
                	}
                	else{
                	    p->index = 0;
                	    first = p;
                	}                           
                }

                wasVisited = true; 
                if (next != NULL){
                    next->tickRecursive(move);    
                }
                else{

                    if (move != NULL){ 
                        delete move; // nie ma nic dalej wiec kasuj     	
                    }
                }

                wasVisited = false;
            }  
		}
};

template <typename type>
ostream& operator<<(ostream& out, Tunnel<type>& t){
    Elem<type>* walk = t.first;
	int i = 0;

	while (i <= t.length){
		if (walk != NULL && i == walk->index){
			out << walk->value;
			walk = walk->next; 
		}
		else{
			out << "_";
		}

		if (i != t.length){
			out << ", ";
		}

		i++;
	}	
    
    t.wasVisited = true;
    if (t.next != NULL && t.next->wasVisited == false){
        out << " > ";   	
  	    out << *t.next;
  	    t.wasVisited = false;
  	    return out; 
  	}
  	else{
  		t.wasVisited = false;
  	    return out;
    }  	            
}