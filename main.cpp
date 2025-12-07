#include <iostream>
#include <iomanip>
using namespace std;

// ===== VARIABEL GLOBAL =====
float hasil[1][4];
float voltageTDS, voltageTurb, voltagePH, voltageTemp;
float calibrationTDS = 1.2;
float clearVolt = 4.2;
float murkyVolt = 2.5;
float offsetPH = 0.15;

// Index kualitas
string indexTDS, indexNTU, indexPH, indexTemp, indexTotal;

void opening()
{
    cout << "\n\n";
    cout << "=================  A Q U A L Y Z E R  ======================\n";
    cout << "            Smart Water Quality Index Analyzer System         \n";
    cout << "--------------------------------------------------------------\n";
    cout << "   Memproses :  TDS  |  Turbidity  |  pH  |  Temperature      \n";
    cout << "   Output    :  Nilai pembacaan dan status kelayakan air      \n";
    cout << "--------------------------------------------------------------\n";
    cout << "   Silahkan masukkan tegangan sensor sesuai pembacaan Anda.   \n";
    cout << "==============================================================\n\n";
}

// ===== FUNGSI INPUT =====
void inputData()
{
    cout << "\n";
    cout << "Tegangan TDS (V)        : ";
    cin >> voltageTDS;

    cout << "Tegangan Turbidity (V)  : ";
    cin >> voltageTurb;

    cout << "Tegangan pH (V)         : ";
    cin >> voltagePH;

    cout << "Tegangan Suhu (V)       : ";
    cin >> voltageTemp;
}

// ===== FUNGSI PERHITUNGAN =====
void hitung()
{

    float tdsValue = voltageTDS * calibrationTDS * 500.0;
    hasil[0][0] = tdsValue;

    float NTU = (clearVolt - voltageTurb) * (100 / (clearVolt - murkyVolt));
    hasil[0][1] = NTU;

    float pHValue = 7.0 + ((2.5 - (voltagePH + offsetPH)) / 0.18);
    hasil[0][2] = pHValue;

    float suhu = voltageTemp * 100.0;
    hasil[0][3] = suhu;

    // Penilaian TDS
    if (tdsValue <= 300)
        indexTDS = "Layak";
    else if (tdsValue <= 1000)
        indexTDS = "Warning";
    else
        indexTDS = "Tidak Layak";

    // Penilaian NTU
    if (NTU < 5)
        indexNTU = "Sangat Jernih";
    else if (NTU <= 25)
        indexNTU = "Cukup Jernih";
    else
        indexNTU = "Keruh";

    // Penilaian pH
    if (pHValue >= 6.5 && pHValue <= 8.5)
        indexPH = "Normal";
    else
        indexPH = "Tidak Normal";

    // Penilaian suhu
    if (suhu >= 20 && suhu <= 30)
        indexTemp = "Normal";
    else
        indexTemp = "Tidak Normal";

    // Penilaian total
    if (indexTDS == "Layak" && NTU < 25 && indexPH == "Normal" && indexTemp == "Normal")
        indexTotal = "LAYAK";
    else
        indexTotal = "TIDAK LAYAK";
}

// ===== FUNGSI OUTPUT =====
void tampilkanHasil()
{

    cout << "\n=================================================================\n";
    cout << "                       HASIL PEMBACAAN SENSOR                    \n";
    cout << "=================================================================\n";

    cout << left << setw(15) << "Parameter"
         << setw(15) << "Nilai"
         << setw(20) << "Satuan"
         << setw(15) << "Indeks" << endl;

    cout << "-----------------------------------------------------------------\n";

    cout << left << setw(15) << "TDS"
         << setw(15) << hasil[0][0]
         << setw(20) << "ppm"
         << setw(15) << indexTDS << endl;

    cout << left << setw(15) << "Kekeruhan"
         << setw(15) << hasil[0][1]
         << setw(20) << "NTU"
         << setw(15) << indexNTU << endl;

    cout << left << setw(15) << "pH"
         << setw(15) << hasil[0][2]
         << setw(20) << "-"
         << setw(15) << indexPH << endl;

    cout << left << setw(15) << "Suhu"
         << setw(15) << hasil[0][3]
         << setw(20) << "°C"
         << setw(15) << indexTemp << endl;

    cout << "-----------------------------------------------------------------\n";

    cout << left << setw(15) << "Status Air"
         << setw(15) << ""
         << setw(20) << ""
         << setw(15) << indexTotal << endl;

    cout << "=================================================================\n";
}

// ====== MAIN =====
int main()
{
    opening();        // Opening / Intro
    inputData();      // Input data
    hitung();         // Proses perhitungan
    tampilkanHasil(); // Output hasil

    return 0;
}