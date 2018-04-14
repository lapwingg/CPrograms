//Kamil Czajka
#include <iostream>

using namespace std;

struct Argument {
    int value;
    Argument *next;

    Argument(int v) : value(v) {
        next = NULL;
    }
};

struct Factor {
    int value;
    Factor *next;

    Factor(int v) : value(v) {
        next = NULL;
    }
};

struct Result {
    long long value;
    Result *next;

    Result(long long v) : value(v) {
        next = NULL;
    }
};

struct Manager {
    int sets;
    int args;
    Argument *first;
    Factor *thisFirst;
    int degree;
    Result *firstInput;

    Manager(int s, int a) : sets(s), args(a) {
        first = NULL;
        thisFirst = NULL;
        firstInput = NULL;
        readArguments(0, first);
    }

    void control(int i) {
        int s;
        long long input;

        if (i < sets) {
            cin >> s;
            degree = s;
            readFactors(0, degree, thisFirst);
            calculateValues(first);
            printValues(firstInput);
            deleteValues(firstInput);
            deleteFactors(thisFirst);
            control(++i);
        }
    }

    void readArguments(int i, Argument *last) {
        int v;
        Argument *newest;

        if (i < args) {
            cin >> v;
            newest = new Argument(v);
            if (first == NULL) {
                first = newest;
            } else {
                last->next = newest;
            }

            readArguments(++i, newest);
        }
    }

    void deleteArguments(Argument *walk) {
        Argument *p;

        if (walk != NULL) {
            first = walk->next;
            p = walk;
            delete p;
            deleteArguments(walk->next);
        }
    }

    void readFactors(int i, int s, Factor *last) {
        int v;
        Factor *newest;

        if (i <= s) {
            cin >> v;
            newest = new Factor(v);
            if (thisFirst == NULL) {
                thisFirst = newest;
            } else {
                last->next = newest;
            }

            readFactors(++i, s, newest);
        }
    }

    void deleteFactors(Factor *walk) {
        Factor *p;

        if (walk != NULL) {
            thisFirst = walk->next;
            p = walk;
            delete p;
            deleteFactors(thisFirst);
        }
    }

    void calculateValues(Argument *walk) {
        long long input;
        Result *newest;

        if (walk != NULL) {
            input = HornerSchema(0, walk->value, thisFirst);
            newest = new Result(input);
            if (firstInput == NULL) {
                createList(newest, NULL, NULL);
            } else {
                createList(newest, firstInput, firstInput->next);
            }

            calculateValues(walk->next);
        }
    }

    long long HornerSchema(int i, int arg, Factor *walk) {
        if (i == degree) {
            return power(arg, degree) * walk->value;
        } else {
            return power(arg, i) * walk->value + HornerSchema(i + 1, arg, walk->next);
        }
    }

    long long power(int arg, int st) {
        if (st == 0) {
            return 1;
        } else {
            return arg * power(arg, st - 1);
        }
    }

    void createList(Result *newest, Result *walkAfter, Result *walk) {
        if (firstInput == NULL) {
            firstInput = newest;
            return;
        } else {
            if (firstInput->next == NULL) {
                if (newest->value <= firstInput->value) {
                    newest->next = firstInput;
                    firstInput = newest;
                    return;
                } else {
                    firstInput->next = newest;
                    return;
                }
            } else {
                if (newest->value <= firstInput->value) {
                    newest->next = firstInput;
                    firstInput = newest;
                    return;
                }

                if (walk != NULL) {
                    if (newest->value >= walkAfter->value && newest->value <= walk->value) {
                        walkAfter->next = newest;
                        newest->next = walk;
                        return;
                    }

                    createList(newest, walk, walk->next);
                } else {
                    walkAfter->next = newest;
                    return;
                }
            }
        }
    }

    void deleteValues(Result *walk) {
        Result *p;

        if (walk != NULL) {
            firstInput = walk->next;
            p = walk;
            delete p;
            deleteValues(firstInput);
        }
    }

    void printArguments(Argument *walk) {
        if (walk != NULL) {
            cout << walk->value << " ";
            printArguments(walk->next);
        }
    }

    void printFactors(Factor *walk) {
        if (walk != NULL) {
            cout << walk->value << " ";
            printFactors(walk->next);
        } else {
            cout << endl;
        }
    }

    void printValues(Result *walk) {
        if (walk != NULL) {
            if (walk != firstInput) cout << " ";
            cout << walk->value;
            printValues(walk->next);
        } else {
            cout << endl;
        }
    }

    ~Manager() {
        deleteArguments(first);
    }
};

int main() {
    int s, a;

    cin >> s >> a;
    Manager *m = new Manager(s, a);
    m->control(0);
    delete m;

    return 0;
}
