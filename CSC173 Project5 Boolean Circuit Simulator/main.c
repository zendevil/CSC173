/*
 * File: main.c
 * Creator: George Ferguson
 * Created: Mon Nov 28 14:11:17 2016
 * Time-stamp: <Mon Nov 28 14:22:27 EST 2016 ferguson>
 */
#include <stdio.h>
#include <stdlib.h>
#include "Circuit.h"

/**
 * Two AND gates connected to make a 3-input AND circuit.
 */
static Circuit* Circuits_and3() {
	Value* in0 = new_Value(false);
	Value* in1 = new_Value(false);
	Value* in2 = new_Value(false);
	Gate* and0 = new_AndGate(in0, in1);
	Gate* and1 = new_AndGate(Gate_getOutput(and0), in2);

	Value** inputs = new_Value_array(3);
	inputs[0] = in0;
	inputs[1] = in1;
	inputs[2] = in2;
	Value** outputs = new_Value_array(1);
	outputs[0] = Gate_getOutput(and1);
	Gate** gates = new_Gate_array(2);
	gates[0] = and0;
	gates[1] = and1;
	return new_Circuit(3, inputs, 1, outputs, 2, gates);
}

static Circuit* Circuits_test() {
	Value* in0 = new_Value(false);
	Value* in1 = new_Value(false);
	Value* in2 = new_Value(false);
	Gate* nand0 = new_NandGate(in0, in1);
	Gate* nand1 = new_NandGate(Gate_getOutput(nand0), in2);
	Value** inputs = new_Value_array(3);
	inputs[0] = in0;
	inputs[1] = in1;
	inputs[2] = in2;
	Value** outputs = new_Value_array(1);
	outputs[0] = Gate_getOutput(nand1);
	Gate** gates = new_Gate_array(2);
	gates[0] = nand0;
	gates[1] = nand1;
	return new_Circuit(3, inputs, 1, outputs, 2, gates);
}

static Circuit* Circuits_a() {
	Value* in0 = new_Value(false);
	Value* in1 = new_Value(false);
	Value* in2 = new_Value(false);
	Gate* inv0 = new_Inverter(in1);
	Gate* and0 = new_AndGate(Gate_getOutput(inv0), in0);
	Gate* and1 = new_AndGate(in1, in2);
	Gate* or0 = new_OrGate(Gate_getOutput(and0), Gate_getOutput(and1));
	Value** inputs = new_Value_array(3);
	inputs[0] = in0;
	inputs[1] = in1;
	inputs[2] = in2;
	Value** outputs = new_Value_array(1);
	outputs[0] = Gate_getOutput(or0);
	Gate** gates = new_Gate_array(4);
	gates[0] = inv0;
	gates[1] = and0;
	gates[2] = and1;
	gates[3] = or0;
	return new_Circuit(3, inputs, 1, outputs, 4, gates);
}

static Circuit* Circuits_b() {
	Value* in0 = new_Value(false);
	Value* in1 = new_Value(false);
	Value* in2 = new_Value(false);
	Gate* inv0 = new_Inverter(in1);
	Gate* nand0 = new_NandGate(in0, Gate_getOutput(inv0));
	Gate* nand1 = new_NandGate(in1, in2);
	Gate* nor0 = new_NorGate(Gate_getOutput(nand0), Gate_getOutput(nand1));
	Value** inputs = new_Value_array(3);
	inputs[0] = in0;
	inputs[1] = in1;
	inputs[2] = in2;
	Value** outputs = new_Value_array(1);
	outputs[0] = Gate_getOutput(nor0);
	Gate** gates = new_Gate_array(4);
	gates[0] = inv0;
	gates[1] = nand0;
	gates[2] = nand1;
	gates[3] = nor0;
	return new_Circuit(3, inputs, 1, outputs, 4, gates);
}

static Circuit* Circuits_c() {
	Value* in0 = new_Value(false);
	Value* in1 = new_Value(false);
	Gate* inv0 = new_Inverter(in0);
	Gate* inv1 = new_Inverter(in1);
	Gate* and0 = new_AndGate(in1, in0);
	Gate* and1 = new_AndGate(Gate_getOutput(inv0), Gate_getOutput(inv1));
	Gate* or0 = new_OrGate(Gate_getOutput(and0), Gate_getOutput(and1));
	Value** inputs = new_Value_array(2);
	inputs[0] = in0;
	inputs[1] = in1;
	Value** outputs = new_Value_array(1);
	outputs[0] = Gate_getOutput(or0);
	Gate** gates = new_Gate_array(5);
	gates[0] = inv0;
	gates[1] = inv1;
	gates[2] = and0;
	gates[3] = and1;
	gates[4] = or0;
	return new_Circuit(2, inputs, 1, outputs, 5, gates);
}

static Circuit *Circuits_1BitAdder() {
	Value* in0 = new_Value(false);
	Value* in1 = new_Value(false);
	Value* in2 = new_Value(false);
	Gate* inv0 = new_Inverter(in0);
	Gate* inv1 = new_Inverter(in1);
	Gate* inv2 = new_Inverter(in2);
	Gate* and1 = new_And3Gate(Gate_getOutput(inv0),Gate_getOutput(inv1), in2);
	Gate* and2 = new_And3Gate(Gate_getOutput(inv0),in1, Gate_getOutput(inv2));
	Gate* and3 = new_And3Gate(Gate_getOutput(inv0),in1, in2);
	Gate* and4 = new_And3Gate(in0,Gate_getOutput(inv1), Gate_getOutput(inv2));
	Gate* and5 = new_And3Gate(in0, Gate_getOutput(inv1), in2);
	Gate* and6 = new_And3Gate(Gate_getOutput(inv2),in1, in0);
	Gate* and7 = new_And3Gate(in0,in1, in2);
	Gate* or0 = new_Or4Gate(Gate_getOutput(and1), Gate_getOutput(and2), Gate_getOutput(and4), Gate_getOutput(and7));
	Gate* or1 = new_Or4Gate(Gate_getOutput(and3), Gate_getOutput(and5), Gate_getOutput(and6), Gate_getOutput(and7));
	Value** inputs = new_Value_array(2);
	inputs[0] = in0;
	inputs[1] = in1;
	inputs[2] = in2;
	Value** outputs = new_Value_array(2);
	outputs[0] = Gate_getOutput(or0);
	outputs[1] = Gate_getOutput(or1);
	Gate** gates = new_Gate_array(12);
	gates[0] = inv0;
	gates[1] = inv1;
	gates[2] = inv2;
	gates[3] = and1;
	gates[4] = and2;
	gates[5] = and3;
	gates[6] = and4;
	gates[7] = and5;
	gates[8] = and6;
	gates[9] = and7;
	gates[10] = or0;
	gates[11] = or1;
	return new_Circuit(3, inputs, 2, outputs, 12, gates);
}

static char* b2s(bool b) {
	return b ? "T" : "F";
}

static void test3In1Out(Circuit* circuit, bool in0, bool in1, bool in2) {
	Circuit_setInput(circuit, 0, in0);
	Circuit_setInput(circuit, 1, in1);
	Circuit_setInput(circuit, 2, in2);
	//Circuit_dump(circuit);
	Circuit_update(circuit);
	bool out0 = Circuit_getOutput(circuit, 0);
	printf("%s %s %s -> %s\n", b2s(in0), b2s(in1), b2s(in2), b2s(out0));
}

static void test2In1Out(Circuit* circuit, bool in0, bool in1) {
	Circuit_setInput(circuit, 0, in0);
	Circuit_setInput(circuit, 1, in1);
	Circuit_update(circuit);
	bool out0 = Circuit_getOutput(circuit, 0);
	printf("%s %s -> %s\n", b2s(in0), b2s(in1), b2s(out0));
}

static void test3In2Out(Circuit *circuit, bool in0, bool in1, bool in2) {
	Circuit_setInput(circuit, 0, in0);
	Circuit_setInput(circuit, 1, in1);
	Circuit_setInput(circuit, 2, in2);
	Circuit_update(circuit);
	bool out0 = Circuit_getOutput(circuit, 0);
	bool out1 = Circuit_getOutput(circuit, 1);
	printf("%s %s %s -> %s %s\n", b2s(in0), b2s(in1), b2s(in2), b2s(out0), b2s(out1));
}

bool tf[2] = {true, false};
void testAllInputs(Circuit* c) {
	if(Circuit_numInputs(c) == 2) {
		for(int i = 0; i<sizeof(tf); i++) {
			for(int j = 0; j<sizeof(tf); j++) {
				test2In1Out(c, tf[i], tf[j]);
			}
		}
	} else if (Circuit_numInputs(c) == 3) {

		for(int i = 0; i<sizeof(tf); i++) {
			for(int j = 0; j<sizeof(tf); j++) {
				for(int k=0; k<sizeof(tf); k++) {
					if(Circuit_numOutputs(c) == 1)
						test3In1Out(c, tf[i], tf[j], tf[k]);
					else if(Circuit_numOutputs(c) == 2) test3In2Out(c, tf[i], tf[j], tf[k]);
					else printf("error\n");
				}
			}
		}

	} else {
		printf("number of inputs is not equal to 2 or 3\n");
	}
}


int main(int argc, char **argv) {

	Circuit* a = Circuits_a();
	printf("(a)\n");
	testAllInputs(a);
	printf("\n");

	Circuit* b = Circuits_b();
	printf("(b)\n");
	testAllInputs(b);
	printf("\n");

	Circuit* c = Circuits_c();
	printf("(c)\n");
	testAllInputs(c);
	printf("\n");

	Circuit* d = Circuits_1BitAdder();
	printf("One Bit Adder\n");
	testAllInputs(d);
	printf("\n");

	print("(TAF)OF");


}
