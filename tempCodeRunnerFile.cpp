#include <iostream>
#include <iomanip>
using namespace std;

// ===== VARIABEL GLOBAL =====
float hasil[1][4];

float voltA_TDS, voltB_TDS, sampelML;
float voltTurb, voltPH, voltTemp;

// Index kualitas
string indexTDS, indexNTU, indexPH, indexTemp, indexTotal;

void opening()
{
    cout << "\n\n";
    cout << "=================  A Q U A L Y Z E R  ======================\n";
    cout << "            Smart Water Quality Index Analyzer System         \n";
    cout << "--------------------------------------------------------------\n";
    cout << "   Silahkan masukkan tegangan sensor sesuai pembacaan Anda.   \n";
    cout << "==============================================================\n\n";
}

// ===== FUNGSI INPUT =====
void inputData() {
    // --- Input untuk TDS ---
    cout << "Tegangan A (TDS) : ";
    cin >> voltA_TDS;
    cout << "Tegangan B (TDS) : ";
    cin >> voltB_TDS;
    cout << "Volume Sampel Air (ml) : ";
    cin >> sampelML;

    // --- Input turbidity ---
    cout << "Tegangan Turbidity (V) : ";
    cin >> voltTurb;

    // --- Input pH dan Suhu (tanpa rumus, hanya untuk standar WHO) ---
    cout << "Nilai pH (Hasil Sensor) : ";
    cin >> voltPH;

    cout << "Nilai Suhu (Celsius, Hasil Sensor) : ";
    cin >> voltTemp;
}

// ===== PERHITUNGAN =====
void hitung() {
    // ======== 1. TDS (rumus baru) =========
    float tdsValue = ((voltA_TDS - voltB_TDS) * 1000) / sampelML;
    hasil[0][0] = tdsValue;

    // ======== 2. TURBIDITY (rumus dari gambar) =========
    // Rumus di gambar:
    // NTU = 3000 * ( (ADCmax - ADC) / ADC )
    // Kita anggap voltage = ADC
    float NTU = 3000 * ((5.0 - voltTurb) / voltTurb);
    hasil[0][1] = NTU;

    // ======== 3. pH (tanpa rumus) =========
    hasil[0][2] = voltPH;

    // ======== 4. Suhu (tanpa rumus) =========
    hasil[0][3] = voltTemp;

    // ======== PENILAIAN BERDASARKAN STANDAR WHO ========

    // --- TDS ---
    if (tdsValue <= 300) indexTDS = "Layak";
    else if (tdsValue <= 1000) indexTDS = "Warning";
    else indexTDS = "Tidak Layak";

    // --- NTU WHO ---
    if (NTU < 5) indexNTU = "Layak (Jernih)";
    else indexNTU = "Tidak Layak (Keruh)";

    // --- pH WHO: 6.5 – 8.5 ---
    if (voltPH >= 6.5 && voltPH <= 8.5) indexPH = "Layak";
    else indexPH = "Tidak Layak";

    // --- SUHU WHO: 20 – 30 °C ---
    if (voltTemp >= 20 && voltTemp <= 30) indexTemp = "Layak";
    else indexTemp = "Tidak Layak";

    // --- Total ---
    if (indexTDS == "Layak" && indexNTU.find("Layak") != string::npos &&
        indexPH == "Layak" && indexTemp == "Layak") {
        indexTotal = "AIR LAYAK DIGUNAKAN";
    } else {
        indexTotal = "AIR TIDAK LAYAK";
    }
}

// ===== OUTPUT =====
void tampilkanHasil() {
    cout << "\n=================================================================\n";
    cout << "                HASIL EVALUASI KUALITAS AIR\n";
    cout << "=================================================================\n";

    cout << left << setw(15) << "Parameter"
         << setw(15) << "Nilai"
         << setw(20) << "Satuan"
         << setw(15) << "Indeks"
         << endl;

    cout << "-----------------------------------------------------------------\n";

    cout << left << setw(15) << "TDS"
         << setw(15) << hasil[0][0]
         << setw(20) << "mg/L"
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

// ===== MAIN =====
int main()
{
    opening();        // Opening / Intro
    inputData();      // Input data
    hitung();         // Proses perhitungan
    tampilkanHasil(); // Output hasil

    return 0;
}