#include <iostream>
#include <chrono>
#include <ctime>
using namespace std;

chrono::system_clock::time_point valida_fecha(int, int, int, int, int, int);

int main(){
    int anio, mes, dia, hora, min, seg;
    cout << "Ingrese la fecha (YYYY MM DD HH MM SS): ";
    cin >> anio >> mes >> dia >> hora >> min >> seg;
    try{
        chrono::system_clock::time_point datoTiempo = valida_fecha(anio, mes, dia, hora, min, seg);
        time_t tiempo = chrono::system_clock::to_time_t(datoTiempo);
        cout << "Fecha y tiempo válidos: " << ctime(&tiempo);
    } catch (const invalid_argument& e){
        cerr << "ERROR " << e.what() << endl;
    }

}
chrono::system_clock::time_point valida_fecha(int anio, int mes, int dia, int hora, int min, int seg){
    tm tiempoinfo = {};
    tiempoinfo.tm_year = anio - 1900;
    tiempoinfo.tm_mon = mes - 1;
    tiempoinfo.tm_mday = dia;
    tiempoinfo.tm_hour = hora;
    tiempoinfo.tm_min = min;
    tiempoinfo.tm_sec = seg;

    time_t tiempo = mktime(&tiempoinfo);
    if (tiempo == -1)  throw invalid_argument("Fecha y tiempo inválidas");
    return chrono::system_clock::from_time_t(tiempo);
}
