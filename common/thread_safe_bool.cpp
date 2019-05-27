/*
PRE: Recibe un valor booleano (bool).
POST: Inicializa un valor booleano protegido 
en hilos
*/
ThreadSafeBool::ThreadSafeBool(bool boolValue)
: boolValue(boolValue) {}

/*Destruye el valor boleano seguro en hilos.*/
ThreadSafeBool::~ThreadSafeBool() = default;

/*Cambia el actual valor a false.*/
ThreadSafeBool::turn_false(){
    this->boolValue = false;
}

/*Devuelve el valor booleano actual.*/
bool ThreadSafeBool::getValue(){
    return this->boolValue;
}
