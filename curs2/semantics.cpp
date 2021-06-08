/* $j17 */
#include "semantics.h"
using namespace std;
void tSM::init(){
	globals.clear();
    locals.clear();
    params.clear();
    scope = 0;
	//константы
	globals["e"] = tgName(VAR | DEFINED | BUILT, "");
	globals["pi"] = tgName(VAR | DEFINED | BUILT, "");
    // элементарные процедуры:
    globals["abs"] = tgName(PROC | DEFINED | BUILT, "", 1);
    globals["atan"] = tgName(PROC | DEFINED | BUILT, "", 1);
    globals["cos"] = tgName(PROC | DEFINED | BUILT, "", 1);
    globals["sin"] = tgName(PROC | DEFINED | BUILT, "", 1);
    globals["tan"] = tgName(PROC | DEFINED | BUILT, "", 1);
    globals["exp"] = tgName(PROC | DEFINED | BUILT, "", 1);
    globals["sqrt"] = tgName(PROC | DEFINED | BUILT, "", 1);
    globals["log"] = tgName(PROC | DEFINED | BUILT, "", 1);
    globals["remainder"] = tgName(PROC | DEFINED | BUILT, "", 2);
    globals["quotient"] = tgName(PROC | DEFINED | BUILT, "", 2);
    globals["expt"] = tgName(PROC | DEFINED | BUILT, "", 2);
	return;}
int tSM::p01(){ //        S -> PROG
    bool error = false;
	string undefinedProc, unusedProc, undefinedVar, unusedVar;
    for (tGlobal::iterator it = globals.begin();
         it != globals.end();
         ++it) {
			if(it->second.test(DEFINED) && !it->second.test(USED) && it->second.test(PROC) && !it->second.test(BUILT)){
				if(!unusedProc.empty()){
					unusedProc += ";\n";
				}
				unusedProc += "'" + it->first + "' on line " + it->second.line;
				error = true;
			}
			if(!it->second.test(DEFINED) && it->second.test(USED) && it->second.test(PROC)){
				if(!undefinedProc.empty()){
					undefinedProc += ";\n";
				}
				undefinedProc += "'" + it->first + "' on line " + it->second.line;
				error = true;
			}
			if(it->second.test(DEFINED) && !it->second.test(USED) && it->second.test(VAR) && !it->second.test(BUILT)){
				if(!unusedVar.empty()){
					unusedVar += ";\n";
				}
				unusedVar += "'" + it->first + "' on line " + it->second.line;
				error = true;
			}
			if(!it->second.test(DEFINED) && it->second.test(USED) && it->second.test(VAR)){
				if(!undefinedVar.empty()){
					undefinedVar += ";\n";
				}
				undefinedVar += "'" + it->first + "' on line " + it->second.line;
				error = true;
			}
    }
    if (error) {
		if(!unusedProc.empty()){
			ferror_message += "Warning[01-1]: the following procedures are not used in the code:\n" + unusedProc +".\n";
			// в коде не используются следующие процедуры:
			// 'f' в строке 1.
			// the following procedures are not used in the code:
			// 'f' on line 1.
		}
		if(!unusedVar.empty()){
			ferror_message += "Warning[01-2]: the following variables are not used in the code:\n" + unusedVar +".\n";
			// следующие переменные не используются в коде:
			// 'y' в строке 4.
			// the following variables are not used in the code:
			// 'y' on line 4.
		}
		if(!undefinedProc.empty()){
			ferror_message += "Error[01-3]: the following procedures do not have a definition in the code:\n" + undefinedProc +".\n";
			return 1;
			// следующие процедуры не имеют определения в коде:
			// 'z' в строке 2.
			// the following procedures do not have a definition in the code:
			// 'z' on line 2.
		}
		if(!undefinedVar.empty()){
			ferror_message += "Error[01-4]: the following variables do not have a definition in the code:\n" + undefinedVar +".\n";
			return 1;
			// следующие переменные не имеют определения в коде
			// 'a' в строке 2.
			// the following variables do not have a definition in the code:
			// 'a' on line 2.
		}
	}
	return 0;}
int tSM::p02(){ //     PROG -> CALCS
	return 0;}
int tSM::p03(){ //     PROG -> DEFS
	return 0;}
int tSM::p04(){ //     PROG -> DEFS CALCS
	return 0;}
int tSM::p05(){ //        E -> $id
	string name = S1->name;
    switch (scope) {
        case 2:
            if (locals.count(name))break;
        case 1:
            if (params.count(name))break;
        default:
            tgName &ref = globals[name];
            if (ref.empty()) {
                ref = tgName(VAR | USED, S1->line);
                break;
            }
            if (ref.test(VAR)) {
                ref.set(USED);
                break;
            }
            if (ref.test(BUILT)) {
                ferror_message +=
                        "Error[05-1] in line " + S1->line + ": the built-in '"
                        + name +
                        "' procedure cannot be used as a variable!\n";
                        // встроенная процедура 'abs' не может использоваться в качестве переменной!
                        // the built-in 'abs' procedure cannot be used as a variable!
                return 1;
            }

            ferror_message +=
                    "Error[05-2] in line " + S1->line + ": the name '"
                    + name +
                    "' cannot be used to refer a variable.\n" +
                    "It was previously declared as a procedure on line " + ref.line + "!\n";
                    // имя 'x' не может использоваться для ссылки на переменную.
					// Ранее это было объявлено как процедура в строке 1!
                    // the name 'x' cannot be used to refer a variable.
					// It was previously declared as a procedure on line 1!
            return 1;
    }
	return 0;}
int tSM::p06(){ //        E -> $int
	return 0;}
int tSM::p07(){ //        E -> $dec
	return 0;}
int tSM::p08(){ //        E -> AREX
	return 0;}
int tSM::p09(){ //        E -> COND
	return 0;}
int tSM::p10(){ //        E -> EASYLET
	return 0;}
int tSM::p11(){ //        E -> CPROC
	return 0;}
int tSM::p12(){ //     AREX -> HAREX E )
	return 0;}
int tSM::p13(){ //    HAREX -> ( AROP
	return 0;}
int tSM::p14(){ //    HAREX -> HAREX E
	return 0;}
int tSM::p15(){ //     AROP -> +
	return 0;}
int tSM::p16(){ //     AROP -> -
	return 0;}
int tSM::p17(){ //     AROP -> *
	return 0;}
int tSM::p18(){ //     AROP -> /
	return 0;}
int tSM::p19(){ //  EASYLET -> HEASYL E )
	scope = 1;
	return 0;}
int tSM::p20(){ //   HEASYL -> ( let ( )
	scope = 2;
	return 0;}
int tSM::p21(){ //   HEASYL -> HEASYL INTER
	return 0;}
int tSM::p22(){ //     COND -> ( cond BRANCHES )
	return 0;}
int tSM::p23(){ // BRANCHES -> CLAUS ELSE
	return 0;}
int tSM::p24(){ //    CLAUS -> ( BOOL E )
	return 0;}
int tSM::p25(){ //     ELSE -> ( else ELSEB )
	return 0;}
int tSM::p26(){ //    ELSEB -> E
	return 0;}
int tSM::p27(){ //    ELSEB -> INTER ELSEB
	return 0;}
int tSM::p28(){ //      STR -> $str
	return 0;}
int tSM::p29(){ //      STR -> SCOND
	return 0;}
int tSM::p30(){ //    SCOND -> ( cond SBRANCHES )
	return 0;}
int tSM::p31(){ //SBRANCHES -> SELSE
	return 0;}
int tSM::p32(){ //SBRANCHES -> SCLAUS SBRANCHES
	return 0;}
int tSM::p33(){ //   SCLAUS -> ( BOOL STR )
	return 0;}
int tSM::p34(){ //    SELSE -> ( else STR )
	return 0;}
int tSM::p35(){ //    CPROC -> HCPROC )
	string name = S1->name;
	tgName &ref = globals[name];
	if(ref.test(DEFINED) && (ref.arity != S1->count)){
		ferror_message += "Error[35-1] in line " + S1->line + 
		": incorrect number of arguments when calling the '" + name + 
		"' procedure.\n\t\t\tNumber of procedure parameters: " + Uint_to_str(ref.arity) + 
		".\nNumber of parameters when calling the procedure on this line: " + Uint_to_str(S1->count) + ".\n";
		return 1;
		// неверное количество аргументов при вызове процедуры 'f'.
		// Количество параметров процедуры: 2.
		// Количество параметров при вызове процедуры на этой строке: 3.
		// incorrect number of arguments when calling the 'f' procedure.
		// Number of procedure parameters: 2.
		// Number of parameters when calling the procedure on this line: 3.
	}
	if(ref.test(USED) && ref.arity != S1->count){
		ferror_message += "Error[35-2] in line " + S1->line + 
		": mismatch in the number of parameters when calling an undefined procedure.\n\tLine "
		+ ref.line + " had " + Uint_to_str(ref.arity) + " parameter(s).\nOn this line it's " +  
		Uint_to_str(S1->count) + " parameter(s)!\n";
		return 1;
		// несоответствие количества параметров при вызове неопределенной процедуры.
		// В строке 2 было 2 параметра.
		// В этой строке 0 параметров!
		// mismatch in the number of parameters when calling an undefined procedure.
		// Line 2 had 2 parameter(s).
		// On this line it's 0 parameter(s)!
	}
	if(!ref.test(USED)){
		ref.set(USED);
		ref.arity = S1->count;
	}
	return 0;}
int tSM::p36(){ //   HCPROC -> ( $id
	string name = S2->name;
	switch (scope){
	case 2:
		if (locals.count(name)){
			ferror_message += "Error[36-1] in line " + S1->line 
			+ ": calling the local variable '" + name + "' as a procedure!\n";
			return 1;
			// вызов локальной переменной 'b' в качестве процедуры!
			// calling the local variable 'b' as a procedure!
		}
    case 1:
        if (params.count(name)){
			ferror_message += "Error[36-2] in line " + S1->line 
			+ ": calling the parameter '" + name + "' as a procedure!\n";
			return 1;
			// вызов параметра 'y' в качестве процедуры!
			// calling the parameter 'y' as a procedure!
		}
    default:
		tgName& ref = globals[name];
		if(ref.empty()){
			ref = tgName(PROC, S1->line);
		}
		if(ref.test(VAR)){
			if(ref.test(BUILT)){
				ferror_message += "Error[36-3] in line " + S1->line + ": the name '" 
				+ name +"' is already used to define the built-in constant!\n";
				return 1;
				// имя 'e' уже используется для определения встроенной константы!
				// the name 'e' is already used to define the built-in constant!
			}
			else{
				ferror_message += "Error[36-4] in line " + S1->line +
				": the name '" + name + "' is already used as a variable on line " +
				ref.line + "!\n";
				return 1;
				// имя 'x' уже используется в качестве переменной в строке 1!
				// the name 'x' is already used as a variable on line 1!
			}
		}
		S1->name = name;
		S1->count = 0;
	}
	return 0;}
int tSM::p37(){ //   HCPROC -> HCPROC E
	(S1->count)++;
	return 0;}
int tSM::p38(){ //     BOOL -> $bool
	return 0;}
int tSM::p39(){ //     BOOL -> $idq
	string name = S1->name;
	switch(scope){
		case 1:
			if(params.count(name))break;
		default:
		tgName &ref = globals[name];
		if(ref.test(PROC)){
			ferror_message += "Error[39-1] in line " + S1->line + 
			": cannot create a variable with name '" + name + 
			"'.\nLine " + ref.line +" already has a procedure with this name.\n";
			return 1;
			// не удается создать переменную с именем " x?".
			// В строке 1 уже есть процедура с таким именем.
			// cannot create a variable with name 'x?'.
			// Line 1 already has a procedure with this name.
		}
		else{	
            ferror_message += "Error[39-2] in line " + S1->line + 
			": the variable with named '" + name + "' does not exist!\n";
			return 1;
			// переменной с именем 'f?' не существует!
			// the variable with named 'f?' does not exist!
		}
	}
	return 0;}
int tSM::p40(){ //     BOOL -> REL
	return 0;}
int tSM::p41(){ //     BOOL -> ( not BOOL )
	return 0;}
int tSM::p42(){ //     BOOL -> CPRED
	return 0;}
int tSM::p43(){ //    CPRED -> HCPRED )
	string name = S1->name;
	tgName &ref = globals[name];
	if(ref.empty()){
		ref = tgName(PROC, S1->line, S1->count, S1->types);
	}
	if(ref.test(USED)){
		if(S1->count != ref.arity){
			ferror_message += "Error[43-1] in line " + S1->line + 
			": different number of parameters when calling the '" + name + "' procedure.\nOn line " + ref.line + " there was(were) " +
			Uint_to_str(ref.arity) + " parameter(s).\nOn this line contains " + Uint_to_str(S1->count) + " parameter(s)!\n";
			return 1;
			// различное количество параметров при вызове процедуры 'x?'.
			// В строке 2 был(о) 1 параметр(а).
			// В этой строке содержится 2 параметр(а)!
			// different number of parameters when calling the 'x?' procedure.
			// On line 2 there was(were) 1 parameter(s).
			// On this line contains 2 parameter(s)!
		}
		if(S1->types != ref.types){
			ferror_message += "Error[43-2] in line " + S1->line + 
			": when the procedure was called again, other parameters were specified.\n\tOn line " + ref.line + 
			" were: (";
			string res, tmp;
			int a = ref.types;
			if(ref.arity > 0){
				tmp = (a%10) ? "loob" : "laer";
				a /= 10;
				for(int i = 1; i < ref.arity; i++){
					tmp += " ,";
					tmp += ((a%10) == 1) ? "loob" : "laer";
					a /= 10;
				}
				for (int i=tmp.length()-1; i>=0; i--){
					res += tmp[i];
				}	
			}
			ferror_message += res + ").\nOn this line, it was called: (";
			a = S1->types;
			res.clear();
			tmp.clear();
			if(S1->count > 0){
				tmp = (a%10) ? "loob" : "laer";
				a /= 10;
				for(int i = 1; i < S1->count; i++){
					tmp += " ,";
					tmp += ((a%10) == 1) ? "loob" : "laer";
					a /= 10;
				}
				for (int i=tmp.length()-1; i>=0; i--){
					res += tmp[i];
				}	
			}
			ferror_message += res + ").\n";
			return 1;
			// при повторном вызове процедуры были заданы другие параметры.
			// В строке 3 были: (real, bool).
			// На этой строке было вызвано: (bool, real).
			// when the procedure was called again, other parameters were specified.
			// On line 3 were: (real, bool).
			// On this line, it was called: (bool, real).
		}
	}
	else{
		ref.set(USED);
	}

	if(ref.test(DEFINED)){
		if(S1->count != ref.arity){
			ferror_message += "Error[43-3] in line " + S1->line + 
			": incorrect number of arguments when calling the '" + name + 
			"' procedure.\n\t\tNumber of procedure parameters: " + Uint_to_str(ref.arity) + 
			".\nNumber of parameters when calling the procedure: " + 
			Uint_to_str(S1->count) + ".\n";
			return 1;
			// неправильное количество аргументов при вызове процедуры 'func?'
			// Количество параметров процедуры: 1.
			// Количество параметров при вызове процедуры: 3.
			// incorrect number of arguments when calling the 'func?' procedure.
			// Number of procedure parameters: 1.
			// Number of parameters when calling the procedure: 3.
		}
		if(S1->types != ref.types){
			ferror_message += "Error[43-4] in line " + S1->line +
			": invalid parameter types are specified.\n\t\t\tProcedure parameter order: (";
			string res, tmp;
			int a = ref.types;
			if(ref.arity > 0){
				tmp = (a%10) ? "loob" : "laer";
				a /= 10;
				for(int i = 1; i < ref.arity; i++){
					tmp += " ,";
					tmp += ((a%10) == 1) ? "loob" : "laer";
					a /= 10;
				}
				for (int i=tmp.length()-1; i>=0; i--){
					res += tmp[i];
				}	
			}
			ferror_message += res + ").\nOrder of parameters when calling the procedure: (";

			res.clear();
			tmp.clear();
			a = S1->types;
			if(S1->count > 0){
				tmp = ((a%10) == 1) ? "loob" : "laer";
				a /= 10;
				for(int i = 1; i < S1->count; i++){
					tmp += " ,";
					tmp += ((a%10) == 1) ? "loob" : "laer";
					a /= 10;
				}
				for (int i=tmp.length()-1; i>=0; i--){
					res += tmp[i];
				}
			}

			ferror_message += res + ").\n";
			return 1;
			// указаны недопустимые типы параметров.
			// Порядок параметров процедуры: (real, real, real).
			// Порядок параметров при вызове процедуры: (real, bool, real).
			// invalid parameter types are specified.
			// Procedure parameter order: (real, real, real).
			// Order of parameters when calling the procedure: (real, bool, real).
		}
	}
	return 0;}
int tSM::p44(){ //   HCPRED -> ( $idq
	string name = S2->name;
	S1->name = name;
	S1->count = 0;
	S1->types = 0;
	return 0;}
int tSM::p45(){ //   HCPRED -> HCPRED ARG
	S1->types *= 10;
	S1->types += ((S2->obj == "1") ? 1 : 0);
	(S1->count)++;
	return 0;}
int tSM::p46(){ //      ARG -> E
	S1->obj = "0";
	return 0;}
int tSM::p47(){ //      ARG -> BOOL
	S1->obj = "1";
	return 0;}
int tSM::p48(){ //      REL -> ( = E E )
	return 0;}
int tSM::p49(){ //      REL -> ( < E E )
	return 0;}
int tSM::p50(){ //      SET -> HSET E )
	return 0;}
int tSM::p51(){ //     HSET -> ( set! $id
	string name = S3->name;
	switch (scope){
	case 2:
		if(locals.count(name)) break;
	case 1:
		if(params.count(name)) break;
	default:
		tgName& ref = globals[name];
		if(ref.empty()){
			ref = tgName(VAR | USED, S1->line);
		}
		if(ref.test(PROC)){
			if(ref.test(BUILT)){
				ferror_message += "Error[51-1] in line " + S1->line + 
				": the assignment operator uses the name of the built-in procedure '" + name +
				"'!\n";
				return 1;
				// оператор присваивания использует имя встроенной процедуры 'abs'!
				// the assignment operator uses the name of the built-in procedure 'abs'!
			}
			else{
				ferror_message += "Error[51-2] in line " + S1->line + 
				": the assignment operator uses the name of the procedure '" + name + "'!\n";
				return 1;
				// оператор присваивания использует имя процедуры 'func'!
				// the assignment operator uses the name of the procedure 'func'!
			}
		}
		if(ref.test(VAR | BUILT)){
			ferror_message += "Error[51-3] in line " + S1->line +
			": the assignment operator uses the name of the built-in constant '" + name + "'!\n";
			return 1;
			// оператор присваивания использует имя встроенной константы 'pi'!
			// the assignment operator uses the name of the built-in constant 'pi'!
		}
	
	}
	return 0;}
int tSM::p52(){ //  DISPSET -> ( display E )
	return 0;}
int tSM::p53(){ //  DISPSET -> ( display BOOL )
	return 0;}
int tSM::p54(){ //  DISPSET -> ( display STR )
	return 0;}
int tSM::p55(){ //  DISPSET -> ( newline )
	return 0;}
int tSM::p56(){ //  DISPSET -> SET
	return 0;}
int tSM::p57(){ //    INTER -> DISPSET
	return 0;}
int tSM::p58(){ //    INTER -> E
	return 0;}
int tSM::p59(){ //    CALCS -> CALC
	return 0;}
int tSM::p60(){ //    CALCS -> CALCS CALC
	return 0;}
int tSM::p61(){ //     CALC -> E
	return 0;}
int tSM::p62(){ //     CALC -> BOOL
	return 0;}
int tSM::p63(){ //     CALC -> STR
	return 0;}
int tSM::p64(){ //     CALC -> DISPSET
	return 0;}
int tSM::p65(){ //     DEFS -> DEF
	return 0;}
int tSM::p66(){ //     DEFS -> DEFS DEF
	return 0;}
int tSM::p67(){ //      DEF -> PRED
	return 0;}
int tSM::p68(){ //      DEF -> VAR
	return 0;}
int tSM::p69(){ //      DEF -> PROC
	return 0;}
int tSM::p70(){ //     PRED -> HPRED BOOL )
	//tgName &ref = globals[S1->name];
	//ref.set(DEFINED);
	scope = 0;
	params.clear();
	return 0;}
int tSM::p71(){ //    HPRED -> PDPAR )
	string name = S1->name;
	tgName &ref = globals[name];
	if(ref.test(USED)){
		if(S1->count != ref.arity){
			ferror_message += "Error[71-1] in line " + S1->line + 
			": incorrect number of arguments when calling the '" + name + 
			"' procedure.\n\t\t\tNumber of procedure parameters: " + Uint_to_str(S1->count) + 
			".\nNumber of parameters when calling the procedure on line " + ref.line + 
			": " + Uint_to_str(ref.arity) + ".\n";
			return 1;
			// неверное количество аргументов при вызове процедуры 'func?'.
			// Количество параметров процедуры: 1.
			// Количество параметров при вызове процедуры на строке 2: 2.
			// incorrect number of arguments when calling the 'func?' procedure.
			// Number of procedure parameters: 1.
			// Number of parameters when calling the procedure on line 2: 2.
		}
		if(S1->types != ref.types){
			ferror_message += "Error[71-2] in line " + S1->line +
			": invalid parameter types are specified.\n\t\t\tProcedure parameter order: (";

			int a = S1->count;
			string res, tmp;

			if(S1->count > 0){
				tmp += (a%10) ? "loob" : "laer";
				a /= 10;
				for(int i = 1; i < S1->count; i++){
					tmp += " ,";
					tmp += ((a%10) == 1) ? "loob" : "laer";
					a /= 10;
				}
			}
			for (int i=tmp.length()-1; i>=0; i--){
				res += tmp[i];
			}	

			ferror_message += res + ").\nOrder of parameters when calling the procedure on line "
			+ ref.line + ": (";

			res.clear();
			tmp.clear();
			a = ref.types;
			if(ref.arity > 0){
				tmp = ((a%10) == 1) ? "loob" : "laer";
				a /= 10;
				for(int i = 1; i < ref.types; i++){
					tmp += " ,";
					tmp += ((a%10) == 1) ? "loob" : "laer";
					a /= 10;
				}
				for (int i=tmp.length()-1; i>=0; i--){
					res += tmp[i];
				}
			}
			ferror_message += res + ").\n";
			return 1;
			// указаны недопустимые типы параметров.
			// Порядок параметров процедуры: (bool).
			// Порядок параметров при вызове процедуры на строке 2: (real).
			// invalid parameter types are specified.
			// Procedure parameter order: (bool).
			// Order of parameters when calling the procedure on line 2: (real).
		}
	}
	ref.arity = S1->count;
	ref.types = S1->types;
	scope = 1;
	ref.set(DEFINED);
	return 0;}
int tSM::p72(){ //    PDPAR -> ( define ( $idq
	string name = S4->name;
	S1->name = name;
	tgName &ref = globals[name];
	if(ref.empty()){
		ref = tgName(PROC, S1->line);
		ref.types = 0;
		return 0;
	}

	string thisline = ref.line;
	if(ref.test(DEFINED)){
		ferror_message += "Error[72-1] in line " + S1->line + 
		": a procedure named '" + name + "' already defined on line " + thisline + "!\n";
		return 1;
		// процедура с именем 'func?' уже определена в строке 1!
		// a procedure named 'func?' already defined on line 1!
	}
	S1->types = 0;
	return 0;}
int tSM::p73(){ //    PDPAR -> PDPAR $idq
	string paramName = S2->name;
	string procName = S1->name;

	if(paramName == procName){
		ferror_message += "Warning [73-1] in line " + S1->line + 
		": the procedure and parameter have the same name '" + procName + "'.\n";
		// процедура и параметр имеют одно и то же имя 'func?'.
		// the procedure and parameter have the same name 'func?'.
	}
	if(params.count(paramName)){
		ferror_message += "Error [73-2] in line " + S1->line + ": in the procedure '" + procName +
		"' the '" + paramName + "' parameter is duplicated!\n";
		return 1;
		// в процедуре "func?" дублирует параметр 'f?'!
		// in the procedure 'func?' the 'f?' parameter is duplicated!
	}

	params.insert(paramName);
	S1->types *= 10;
	S1->types += 1;
	(S1->count)++;
	return 0;}
int tSM::p74(){ //    PDPAR -> PDPAR $id
	string paramName = S2->name;
	string procName = S1->name;

	if(params.count(paramName)){
		ferror_message += "Error [74-1] in line " + S1->line + ": in the procedure '" + procName +
		"' the '" + paramName + "' parameter is duplicated!\n";
		return 1;
		// в процедуре 'func?' дублируется параметр 'y'!
		// in the procedure 'func?' the 'y' parameter is duplicated!
	}
	params.insert(paramName);
	S1->types *= 10;
	(S1->count)++;
	return 0;}
int tSM::p75(){ //      VAR -> VARDCL E )
	tgName & ref = globals[S1->name];
	ref.set(DEFINED);
	return 0;}
int tSM::p76(){ //   VARDCL -> ( define $id
	string name = S3->name;
	S1->name = name;
	tgName &ref = globals[name];
	if (ref.empty()) {
		ref = tgName(VAR, S1->line);
		return 0;
    }

	string thisline = ref.line;
	if(ref.test(VAR | BUILT)){
	 	ferror_message += "Error [76-1] in line " + S1->line +
 		": the built-in name '" + name + "' cannot be used to define a new variable!\n";
		return 1;
		// встроенное имя 'pi' не может использоваться для определения новой переменной
		// the built-in name 'pi' cannot be used to define a new variable!
	}
	if(ref.test(VAR | DEFINED)){
		ferror_message += "Error [76-2] in line " + S1->line + ": the name '" + name +
		"' was previously used to define a variable on line "+ thisline +"!\n";
		return 1;
		// имя 'a' ранее использовалось для определения переменной в строке 1!
		// the name 'a' was previously used to define a variable on line 1!
	}
	if(ref.test(PROC | BUILT)){
		ferror_message += "Error [76-3] in line " + S1->line +
	 	": the built-in '" + name + "' procedure cannot be used to define a variable!\n";
		return 1;
		// встроенная процедура 'abs' не может использоваться для определения переменной!
		// the built-in 'abs' procedure cannot be used to define a variable!
	}
	if(ref.test(PROC | DEFINED)){
		ferror_message += "Error [76-4] in line " + S1->line + ": the name '" + name + 
		"' cannot be used to define a variable,\nbecause it is used to define a procedure on line " 
 		+ thisline + "!\n";
		return 1;
		// имя 'func' не может использоваться для определения переменной,
		// поскольку оно используется для определения процедуры в строке 1!
		// the name 'func' cannot be used to define a variable,
		// because it is used to define a procedure on line 1!
	}
	if(ref.test(PROC | USED)){
		ferror_message += "Error [76-5] in line " + S1->line + ": the name '" + name +
		"' cannot be used to define a variable,\nbecause this is the name of the procedure on line "
 		+ thisline + "!\n";
		return 1;
		// имя 'func' не может использоваться для определения переменной,
		// потому что это название процедуры в строке 2!
		// the name 'func' cannot be used to define a variable,
		// because this is the name of the procedure on line 2!
	}
	return 0;}
int tSM::p77(){ //     PROC -> HPROC BLOCK )
	scope = 0;
	params.clear();
	return 0;}
int tSM::p78(){ //     PROC -> HPROC E )
	params.clear();
	scope = 0;
	return 0;}
int tSM::p79(){ //    HPROC -> PCPAR )
	string name = S1->name;
	tgName &ref = globals[name];
	if(ref.test(USED) && S1->count != ref.arity){
		ferror_message += "Error[79-1] in line " + S1->line + 
		": incorrect number of arguments when calling the '" + name + 
		"' procedure.\n\t\t\tNumber of procedure parameters: " + Uint_to_str(S1->count) + 
		".\nNumber of parameters when calling the procedure on line "+ ref.line + ": " + Uint_to_str(ref.arity) + ".\n";
		return 1;
		// неверное количество аргументов при вызове процедуры 'f'.
		// Количество параметров процедуры: 2.
		// Количество параметров при вызове процедуры в строке 2: 1.
		// incorrect number of arguments when calling the 'f' procedure.
		// Number of procedure parameters: 2.
		// Number of parameters when calling the procedure on line 2: 1.
	}
	ref.arity = S1->count;
	scope = 1;
	return 0;}
int tSM::p80(){ //    HPROC -> HPROC INTER
	return 0;}
int tSM::p81(){ //    PCPAR -> ( define ( $id
	string name = S4->name;
	S1->name = name;
	tgName &ref = globals[name];
	if(ref.empty()){
		ref = tgName(PROC | DEFINED, S1->line);
		S1->count = 0;
		return 0;
	}
	string thisline = ref.line;
	if(ref.test(PROC | BUILT)){
		ferror_message += "Error [81-1] in line " + S1->line +": name of the built-in procedure '" + name
		+ "' cannot be used to define a new procedure!\n";
		return 1;
		// имя встроенной процедуры 'abs' не может быть использовано для определения новой процедуры!
		// name of the built-in procedure 'abs' cannot be used to define a new procedure!
	}
	if(ref.test(PROC | DEFINED)){
		ferror_message += "Error [81-2] in line " + S1->line +
		": a procedure with name '" + name+"' has already been defined on the line " + thisline + "!\n"; 
		return 1;
		// процедура с именем 'func' уже определена в строке 1!
		// a procedure with name 'func' has already been defined on the line 1!
	}
	if(ref.test(PROC | USED)){
		ref.set(DEFINED);
		S1->count = 0;
	}
	if(ref.test(VAR | BUILT)){
		ferror_message += "Error [81-3] in line " + S1->line + ": name of the built-in constant '" + name
		+ "' cannot be used to define a new procedure!\n";
		return 1;
		// имя встроенной константы 'e' не может быть использовано для определения новой процедуры!
		// name of the built-in constant 'e' cannot be used to define a new procedure!
	}
	if(ref.test(VAR | DEFINED)){
		ferror_message += "Error [81-4] in line " + S1->line + ": the name '" + name + 
		"' cannot be used to define a procedure,\nbecause it is used to define a variable on the line " 
	 	+ thisline + "!\n";
		return 1;
		// имя 'z' нельзя использовать для определения процедуры,
		// потому что он используется для определения переменной в строке 1!
		// the name 'z' cannot be used to define a procedure,
		// because it is used to define a variable on the line 1!
	}
	if(ref.test(VAR | USED)){
		ferror_message += "Error [81-5] in line " + S1->line + ": the name '" + name +
		"' cannot be used to define a procedure,\nbecause this is the name of the variable on the line "
 		+ thisline + "!\n";
		return 1;
		// имя 'z' нельзя использовать для определения процедуры,
		// потому что это имя переменной в строке 2!
		// the name 'z' cannot be used to define a procedure,
		// because this is the name of the variable on the line 2!
	}
	return 0;
	}
int tSM::p82(){ //    PCPAR -> PCPAR $id
	string paramName = S2->name;
	string procName = S1->name;
	if(paramName == procName){
		ferror_message += "Warning [82-1] in line " + S1->line + 
		": the procedure and parameter have the same name '" + procName + "'.\n";
		// процедура и параметр имеют одно и то же имя 'f'.
		// the procedure and parameter have the same name 'f'.
	}
	if(params.count(paramName)){
		ferror_message += "Error [82-2] in line " + S1->line + ": in the procedure '" + procName +
		"' the '" + paramName + "' parameter is duplicated!\n";
		return 1;
		// в процедуре 'f' параметр 'x' дублируется!
		// in the procedure 'f' the 'x' parameter is duplicated!
	}

	params.insert(paramName);
	(S1->count)++;
	
	return 0;}
int tSM::p83(){ //    BLOCK -> HBLOCK E )
	locals.clear();
	scope = 1;
	return 0;}
int tSM::p84(){ //   HBLOCK -> BLVAR )
	return 0;}
int tSM::p85(){ //   HBLOCK -> HBLOCK INTER
	return 0;}
int tSM::p86(){ //    BLVAR -> ( let ( LOCDEF
	scope = 2;
	return 0;}
int tSM::p87(){ //    BLVAR -> BLVAR LOCDEF
	return 0;}
int tSM::p88(){ //   LOCDEF -> ( $id E )
	string name = S2->name;
	tgName& ref = globals[name];
	if(locals.count(name)){
		ferror_message += "Error[88-1] in line " + S1->line +
		": redefining the local variable '" + name + "'!\n";
		return 1;
		// переопределение локальной переменной 'a'!
		// redefining the local variable 'a'!
	}
	else{
		locals.insert(name);			
	}
	
	return 0;}
//_____________________
int tSM::p89(){return 0;} int tSM::p90(){return 0;} 
int tSM::p91(){return 0;} int tSM::p92(){return 0;} 
int tSM::p93(){return 0;} int tSM::p94(){return 0;} 
int tSM::p95(){return 0;} int tSM::p96(){return 0;} 
int tSM::p97(){return 0;} int tSM::p98(){return 0;} 
int tSM::p99(){return 0;} int tSM::p100(){return 0;} 
int tSM::p101(){return 0;} int tSM::p102(){return 0;} 
int tSM::p103(){return 0;} int tSM::p104(){return 0;} 
int tSM::p105(){return 0;} int tSM::p106(){return 0;} 
int tSM::p107(){return 0;} int tSM::p108(){return 0;} 
int tSM::p109(){return 0;} int tSM::p110(){return 0;} 


