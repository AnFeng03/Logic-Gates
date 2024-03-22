#include <stdio.h>
#include <stdlib.h>
#include "Circuit.h"

static Circuit circuitA(void) {
    char *title = "Circuit A: (NOT(x AND y) AND (x OR y))";

    // Create the inputs
    int NINPUTS = 2;
    Boolean x = new_Boolean(false);
    Boolean y = new_Boolean(false);
    Boolean* inputs = new_Boolean_array(NINPUTS);
    inputs[0] = x;
    inputs[1] = y;

    // Create the outputs
    int NOUTPUTS = 1;
    Boolean result = new_Boolean(false);
    Boolean* outputs = new_Boolean_array(NOUTPUTS);
    outputs[0] = result;

    // Create the gates
    int NGATES = 4;
    Gate andGate = new_AndGate();
    Gate orGate = new_OrGate();
    Gate notGate = new_Inverter();
    Gate andGate2 = new_AndGate();
    Gate* gates = new_Gate_array(NGATES);
    gates[0] = andGate;
    gates[1] = orGate;
    gates[2] = notGate;
    gates[3] = andGate2;

    // Create the circuit
    Circuit circuit = new_Circuit(title,
                                  NINPUTS, inputs,
                                  NOUTPUTS, outputs,
                                  NGATES, gates);

    // Connect the gates in the circuit
    Circuit_connect(circuit, x, Gate_getInput(andGate, 0));
    Circuit_connect(circuit, y, Gate_getInput(andGate, 1));
    Boolean x_and_y = Gate_getOutput(andGate);

    Circuit_connect(circuit, x, Gate_getInput(orGate, 0));
    Circuit_connect(circuit, y, Gate_getInput(orGate, 1));
    Boolean x_or_y = Gate_getOutput(orGate);

    Circuit_connect(circuit, x_and_y, Gate_getInput(notGate, 0));
    Boolean not_x_and_y = Gate_getOutput(notGate);

    Circuit_connect(circuit, not_x_and_y, Gate_getInput(andGate2, 0));
    Circuit_connect(circuit, x_or_y, Gate_getInput(andGate2, 1));
    Boolean final_result = Gate_getOutput(andGate2);

    Circuit_connect(circuit, final_result, result);
    return circuit;
}

static Circuit circuitB(void) {
    char *title = "Circuit B: ((x NOR y) NOR (x NOR y))";

    // Create the inputs
    int NINPUTS = 2;
    Boolean x = new_Boolean(false);
    Boolean y = new_Boolean(false);
    Boolean* inputs = new_Boolean_array(NINPUTS);
    inputs[0] = x;
    inputs[1] = y;

    // Create the outputs
    int NOUTPUTS = 1;
    Boolean result = new_Boolean(false);
    Boolean* outputs = new_Boolean_array(NOUTPUTS);
    outputs[0] = result;

    // Create the gates
    int NGATES = 3;
    Gate norGate1 = new_NorGate();
    Gate norGate2 = new_NorGate();
    Gate norGate3 = new_NorGate();
    Gate* gates = new_Gate_array(NGATES);
    gates[0] = norGate1;
    gates[1] = norGate2;
    gates[2] = norGate3;

    // Create the circuit
    Circuit circuit = new_Circuit(title,
                                  NINPUTS, inputs,
                                  NOUTPUTS, outputs,
                                  NGATES, gates);

    // Connect the gates in the circuit
    Circuit_connect(circuit, x, Gate_getInput(norGate1, 0));
    Circuit_connect(circuit, y, Gate_getInput(norGate1, 1));
    Boolean x_nor_y = Gate_getOutput(norGate1);

    Circuit_connect(circuit, x, Gate_getInput(norGate2, 0));
    Circuit_connect(circuit, y, Gate_getInput(norGate2, 1));
    Boolean x_nor_y2 = Gate_getOutput(norGate2);

    Circuit_connect(circuit, x_nor_y, Gate_getInput(norGate3, 0));
    Circuit_connect(circuit, x_nor_y2, Gate_getInput(norGate3, 1));
    Boolean final_result = Gate_getOutput(norGate3);

    Circuit_connect(circuit, final_result, result);

    return circuit;
}


static Circuit circuitC(void) {
    char *title = "Circuit C: (((x OR y) AND (x OR z)) AND (y OR z))";

    // Create the inputs
    int NINPUTS = 3;
    Boolean x = new_Boolean(false);
    Boolean y = new_Boolean(false);
    Boolean z = new_Boolean(false);
    Boolean* inputs = new_Boolean_array(NINPUTS);
    inputs[0] = x;
    inputs[1] = y;
    inputs[2] = z;

    // Create the outputs
    int NOUTPUTS = 1;
    Boolean result = new_Boolean(false);
    Boolean* outputs = new_Boolean_array(NOUTPUTS);
    outputs[0] = result;

    // Create the gates
    int NGATES = 5;
    Gate orGate1 = new_OrGate();
    Gate orGate2 = new_OrGate();
    Gate orGate3 = new_OrGate();
    Gate andGate1 = new_AndGate();
    Gate andGate2 = new_AndGate();
    Gate* gates = new_Gate_array(NGATES);
    gates[0] = orGate1;
    gates[1] = orGate2;
    gates[2] = orGate3;
    gates[3] = andGate1;
    gates[4] = andGate2;

    // Create the circuit
    Circuit circuit = new_Circuit(title,
                                  NINPUTS, inputs,
                                  NOUTPUTS, outputs,
                                  NGATES, gates);

    // Connect the gates in the circuit
    Circuit_connect(circuit, x, Gate_getInput(orGate1, 0));
    Circuit_connect(circuit, y, Gate_getInput(orGate1, 1));
    Boolean x_or_y = Gate_getOutput(orGate1);

    Circuit_connect(circuit, x, Gate_getInput(orGate2, 0));
    Circuit_connect(circuit, z, Gate_getInput(orGate2, 1));
    Boolean x_or_z = Gate_getOutput(orGate2);

    Circuit_connect(circuit, y, Gate_getInput(orGate3, 0));
    Circuit_connect(circuit, z, Gate_getInput(orGate3, 1));
    Boolean y_or_z = Gate_getOutput(orGate3);

    Circuit_connect(circuit, x_or_y, Gate_getInput(andGate1, 0));
    Circuit_connect(circuit, x_or_z, Gate_getInput(andGate1, 1));
    Boolean x_or_y_and_x_or_z = Gate_getOutput(andGate1);

    Circuit_connect(circuit, x_or_y_and_x_or_z, Gate_getInput(andGate2, 0));
    Circuit_connect(circuit, y_or_z, Gate_getInput(andGate2, 1));
    Boolean final_result = Gate_getOutput(andGate2);

    Circuit_connect(circuit, final_result, result);

    return circuit;
}


static void testCircuit(Circuit circuit, int numInputs, int numOutputs) {
    int maxCombinations = 1 << numInputs;

    for (int i = 0; i < maxCombinations; i++) {
        // Set inputs
        for (int j = 0; j < numInputs; j++) {
            Circuit_setInput(circuit, numInputs - 1 - j, (i >> j) & 1);
        }
        Circuit_update(circuit);

        // Print input combination
        for (int j = numInputs - 1; j >= 0; j--) {
            printf("%d ", (i >> j) & 1);
        }

        // Print output values
        printf("-> ");
        for (int j = 0; j < numOutputs; j++) {
            printf("%s ", Boolean_toString(Circuit_getOutput(circuit, j)));
        }
        printf("\n");
    }
}



//Extra credit section
static Circuit circuitFG(void) {
    char *title = "Circuit FG: f and g functions";

    // Create the inputs
    int NINPUTS = 3;
    Boolean a = new_Boolean(false);
    Boolean b = new_Boolean(false);
    Boolean c = new_Boolean(false);
    Boolean* inputs = new_Boolean_array(NINPUTS);
    inputs[0] = a;
    inputs[1] = b;
    inputs[2] = c;

    // Create the outputs
    int NOUTPUTS = 2;
    Boolean f_result = new_Boolean(false);
    Boolean g_result = new_Boolean(false);
    Boolean* outputs = new_Boolean_array(NOUTPUTS);
    outputs[0] = f_result;
    outputs[1] = g_result;

    int NGATES = 13;

    Gate notA = new_Inverter();
    Gate notB = new_Inverter();
    Gate notC = new_Inverter();

    Gate fAND1 = new_And3Gate();
    Gate fAND2 = new_And3Gate();
    Gate fAND3 = new_And3Gate();
    Gate fAND4 = new_And3Gate();

    Gate gAND1 = new_And3Gate();
    Gate gAND2 = new_And3Gate();
    Gate gAND3 = new_And3Gate();
    Gate gAND4 = new_And3Gate();

    Gate fOR = new_Or4Gate();
    Gate gOR = new_Or4Gate();

    Gate* gates = new_Gate_array(NGATES);
    gates[0] = notA;
    gates[1] = notB;
    gates[2] = notC;
    gates[3] = fAND1;
    gates[4] = fAND2;
    gates[5] = fAND3;
    gates[6] = fAND4;
    gates[7] = gAND1;
    gates[8] = gAND2;
    gates[9] = gAND3;
    gates[10] = gAND4;
    gates[11] = fOR;
    gates[12] = gOR;

    // Create the circuit
    Circuit circuit = new_Circuit(title,
                                  NINPUTS, inputs,
                                  NOUTPUTS, outputs,
                                  NGATES, gates);

    //Creating the not values
    Circuit_connect(circuit, a, Gate_getInput(notA, 0));
    Boolean nota = Gate_getOutput(notA);

    Circuit_connect(circuit, b, Gate_getInput(notB, 0));
    Boolean notb = Gate_getOutput(notB);

    Circuit_connect(circuit, c, Gate_getInput(notC, 0));
    Boolean notc = Gate_getOutput(notC);


    //AND gates for minterms of circuit f
    Circuit_connect(circuit, nota, Gate_getInput(fAND1, 0));
    Circuit_connect(circuit, notb, Gate_getInput(fAND1, 1));
    Circuit_connect(circuit, c, Gate_getInput(fAND1, 2));
    Boolean fand1 = Gate_getOutput(fAND1);

    Circuit_connect(circuit, nota, Gate_getInput(fAND2, 0));
    Circuit_connect(circuit, b, Gate_getInput(fAND2, 1));
    Circuit_connect(circuit, notc, Gate_getInput(fAND2, 2));
    Boolean fand2 = Gate_getOutput(fAND2);

    Circuit_connect(circuit, nota, Gate_getInput(fAND3, 0));
    Circuit_connect(circuit, b, Gate_getInput(fAND3, 1));
    Circuit_connect(circuit, c, Gate_getInput(fAND3, 2));
    Boolean fand3 = Gate_getOutput(fAND3);

    Circuit_connect(circuit, a, Gate_getInput(fAND4, 0));
    Circuit_connect(circuit, b, Gate_getInput(fAND4, 1));
    Circuit_connect(circuit, c, Gate_getInput(fAND4, 2));
    Boolean fand4 = Gate_getOutput(fAND4);


    //AND gates for minterms of circuit g
    Circuit_connect(circuit, nota, Gate_getInput(gAND1, 0));
    Circuit_connect(circuit, notb, Gate_getInput(gAND1, 1));
    Circuit_connect(circuit, c, Gate_getInput(gAND1, 2));
    Boolean gand1 = Gate_getOutput(gAND1);

    Circuit_connect(circuit, nota, Gate_getInput(gAND2, 0));
    Circuit_connect(circuit, b, Gate_getInput(gAND2, 1));
    Circuit_connect(circuit, notc, Gate_getInput(gAND2, 2));
    Boolean gand2 = Gate_getOutput(gAND2);

    Circuit_connect(circuit, a, Gate_getInput(gAND3, 0));
    Circuit_connect(circuit, notb, Gate_getInput(gAND3, 1));
    Circuit_connect(circuit, notc, Gate_getInput(gAND3, 2));
    Boolean gand3 = Gate_getOutput(gAND3);

    Circuit_connect(circuit, a, Gate_getInput(gAND4, 0));
    Circuit_connect(circuit, b, Gate_getInput(gAND4, 1));
    Circuit_connect(circuit, c, Gate_getInput(gAND4, 2));
    Boolean gand4 = Gate_getOutput(gAND4);

    //Creating the OR gates
    Circuit_connect(circuit, fand1, Gate_getInput(fOR, 0));
    Circuit_connect(circuit, fand2, Gate_getInput(fOR, 1));
    Circuit_connect(circuit, fand3, Gate_getInput(fOR, 2));
    Circuit_connect(circuit, fand4, Gate_getInput(fOR, 3));
    Boolean f_final = Gate_getOutput(fOR);

    Circuit_connect(circuit, gand1, Gate_getInput(gOR, 0));
    Circuit_connect(circuit, gand2, Gate_getInput(gOR, 1));
    Circuit_connect(circuit, gand3, Gate_getInput(gOR, 2));
    Circuit_connect(circuit, gand4, Gate_getInput(gOR, 3));
    Boolean g_final = Gate_getOutput(gOR);

    // Connect the outputs
    Circuit_connect(circuit, f_final, f_result);
    Circuit_connect(circuit, g_final, g_result);

    return circuit;
}


int main(int argc, char **argv) {

    //create and test circuit A
    Circuit circuit = circuitA();
    Circuit_dump(circuit);
    printf("\nTesting all input combinations for circuit A:\n");
    testCircuit(circuit, 2,1);
    free_Circuit(circuit);
    printf("\n\n");

    //create and test circuit B
    Circuit circuit1 = circuitB();
    Circuit_dump(circuit1);
    printf("\nTesting all input combinations for circuit B:\n");
    testCircuit(circuit1, 2,1);
    free_Circuit(circuit1);
    printf("\n\n");

    //create and test circuit C
    Circuit circuit2 = circuitC();
    Circuit_dump(circuit2);
    printf("\nTesting all input combinations for circuit C:\n");
    testCircuit(circuit2, 3, 1);
    free_Circuit(circuit2);
    printf("\n\n");

    //create and test circuit FG (extra credit)
    Circuit circuit3 = circuitFG();
    Circuit_dump(circuit3);
    printf("\nTesting all input combinations for circuit FG:\n");
    testCircuit(circuit3, 3, 2);
    free_Circuit(circuit3);

    return 0;
}
