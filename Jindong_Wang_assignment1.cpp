/*******************************************************
 * Academic Integrity & AI Usage Declaration
 *
 * This assignment was completed independently by me.
 * I developed and implemented the program logic myself.
 *
 * I consulted online resources (including GitHub examples)
 * to better understand C++ syntax and structure.
 *
 * I also used AI tools to help improve the grammar and
 * clarity of comments in the code. The computational logic,
 * physics formula implementation, and program structure
 * were written and understood by me.
 *
 * Student: Jindong Wang
 * Student ID: 11072535
 * Course: PHYS30762
 *******************************************************
 * This program calculates the photon energy emitted in a
 * Bohr-model electron transition for a hydrogen-like atom.
 *
 * In the Bohr model, an electron can only occupy discrete
 * energy levels labelled by the principal quantum number n.
 * When the electron drops from a higher level (n_i) to a lower
 * level (n_j), it releases energy as a photon.
 *
 * The photon energy (in electron-volts) is given by:
 *   E = 13.6 * Z^2 * ( 1/n_j^2 - 1/n_i^2 )  eV
 *
 * where:
 *   - Z is the atomic number (1 for H, 2 for He+, etc.)
 *   - n_i is the initial principal quantum number
 *   - n_j is the final principal quantum number
 *
 * The user can choose to display the result in eV or Joules,
 * and the program can repeat calculations until the user quits.
 *******************************************************/

#include <iostream>   // For cin, cout, endl (input/output)
#include <limits>     // For numeric_limits used when clearing input
#include <cmath>      // For math operations (not strictly required here, but ok)
#include <cctype>     // For tolower() to handle E/e and J/j

using std::cin;       // Use cin without writing std::cin everywhere
using std::cout;      // Use cout without writing std::cout everywhere
using std::endl;      // Use endl without writing std::endl everywhere

// Physical constant conversion:
// 1 electron-volt (eV) = 1.602176634 × 10^-19 Joules (J)
constexpr double EV_TO_J = 1.602176634e-19;

/*
 * Function: clearBadInput
 * -----------------------------------------------------
 * Purpose:
 *   If the user types something invalid (e.g. letters instead of numbers),
 *   the input stream enters a "failed" state. This function resets cin
 *   so we can safely ask for input again.
 *
 * Input:
 *   None (void)
 *
 * Output:
 *   None (void)
 *
 * Type signature:
 *   void clearBadInput()
 *
 * How it works (computationally):
 *   - cin.clear() resets error flags (so cin can read again).
 *   - cin.ignore(...) discards the remaining characters on the line.
 *
 * Physical meaning:
 *   No physics here—this is purely about robust user input handling.
 */
void clearBadInput() {
    cin.clear(); // Clear cin error flags (e.g., failbit) so input can continue
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // Ignore everything left on this input line until newline,
    // preventing leftover junk from breaking the next input attempt.
}

/*
 * Function: energyEv
 * -----------------------------------------------------
 * Purpose:
 *   Compute the photon energy (in eV) for an electron transition in the
 *   Bohr model of a hydrogen-like atom.
 *
 * Inputs (with types):
 *   - int Z  : atomic number (positive integer)
 *   - int ni : initial principal quantum number (positive integer)
 *   - int nj : final principal quantum number (positive integer)
 *
 * Output (with type):
 *   - double : photon energy in electron-volts (eV)
 *
 * Type signature:
 *   double energyEv(int Z, int ni, int nj)
 *
 * Physics meaning:
 *   In the Bohr model, energy levels scale like -Z^2 / n^2.
 *   The energy difference between two levels becomes photon energy.
 *
 * Mathematical meaning:
 *   E = 13.6 * Z^2 * (1/nj^2 - 1/ni^2)  eV
 *   For emission, we require ni > nj, so the bracket is positive.
 */
double energyEv(int Z, int ni, int nj) {
    // Convert Z to double and square it: Z^2
    const double Z2 = static_cast<double>(Z) * static_cast<double>(Z);

    // Compute the bracket term: (1/nj^2 - 1/ni^2)
    // We force floating-point division by writing 1.0 (not 1).
    const double term =
        (1.0 / (static_cast<double>(nj) * nj)) - // 1/nj^2
        (1.0 / (static_cast<double>(ni) * ni));  // 1/ni^2

    // Multiply by 13.6 eV (hydrogen ground state magnitude) and Z^2 scaling
    return 13.6 * Z2 * term; // Final photon energy in eV
}

int main() {
    // Friendly title so the user knows what the program is
    cout << "Bohr transition energy calculator" << endl;

    // Repeat calculations until the user says "n"
    while (true) {
        // Variables for user input:
        // Z  = atomic number
        // ni = initial quantum number
        // nj = final quantum number
        int Z = 0, ni = 0, nj = 0;

        // unit chooses output: 'e' for eV, 'j' for Joules
        char unit = 'e';

        // Prompt message (course-style)
        cout << "Enter Z ni nj Units (J for Joules, E for eV), e.g. '1 2 1 J': ";

        // Try to read four values from the user.
        // If the user types the wrong format (e.g., 'a b c d'), cin fails.
        if (!(cin >> Z >> ni >> nj >> unit)) {
            cout << "Invalid input format. Please enter: integer integer integer char" << endl;
            clearBadInput(); // Reset cin and discard the bad input line
            continue;        // Restart the loop and ask again
        }

        // Convert unit to lowercase so 'J' and 'j' behave the same,
        // and 'E' and 'e' behave the same.
        unit = static_cast<char>(std::tolower(static_cast<unsigned char>(unit)));

        // ---------- Input validation (physics + format) ----------

        // Z must be positive (no atom has Z <= 0)
        if (Z <= 0) {
            cout << "Error: Z must be a positive integer." << endl;
            continue; // Ask again
        }

        // ni and nj must be positive integers (quantum number n starts at 1)
        if (ni <= 0 || nj <= 0) {
            cout << "Error: ni and nj must be positive integers." << endl;
            continue;
        }

        // For photon emission using this formula, we enforce ni > nj
        // (electron drops to a lower level → energy released).
        if (ni <= nj) {
            cout << "Error: require ni > nj for this transition." << endl;
            continue;
        }

        // Unit must be either 'e' (electron-volts) or 'j' (Joules)
        if (unit != 'j' && unit != 'e') {
            cout << "Error: Units must be J/j (Joules) or E/e (electron-volts)." << endl;
            continue;
        }

        // ---------- Physics calculation ----------

        // Compute the energy difference in eV using Bohr model formula
        const double E_eV = energyEv(Z, ni, nj);

        // Convert to Joules if needed using the physical conversion constant
        const double E_J  = E_eV * EV_TO_J;

        // ---------- Output ----------

        // If the user asked for eV, print in eV
        if (unit == 'e') {
            cout << "Energy of transition: " << E_eV << " eV" << endl;
        }
        // Otherwise print in Joules
        else {
            cout << "Energy of transition: " << E_J << " J" << endl;
        }

        // ---------- Repeat prompt ----------

        cout << "Calculate another? (y/n): ";

        char again = 'n';    // Default to 'n' so program stops unless user says 'y'
        cin >> again;        // Read the user's decision (one character)

        // Convert again to lowercase so Y/y both mean "yes"
        again = static_cast<char>(std::tolower(static_cast<unsigned char>(again)));

        // If user does not type 'y', exit the loop and end the program
        if (again != 'y') {
            break;
        }
    }

    // Return 0 means the program finished successfully (standard convention)
    return 0;
}
