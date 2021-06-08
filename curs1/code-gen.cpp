/* $j17 */
#include "code-gen.h"
using namespace std;
void tCG::init(){declarations.clear();
 Authentication = "KMS";
//                  ^ 
// replace with your initials!!! 
}
int tCG::p01(){ // S -> PROG
  string header ="/*  " + Authentication +"   */\n";
  header += "#include \"mlisp.h\"\n";
  header += declarations;
  header += "//________________ \n";
  S1->obj = header + S1->obj;
	return 0;}
int tCG::p02(){ //     PROG -> CALCS
	S1->obj = "int main(){\n " + S1->obj
    + "std::cin.get();\n\t return 0;\n\t }\n";
	return 0;}
int tCG::p03(){ //     PROG -> DEFS
 	S1->obj += "int main(){\n "
    "display(\"No calculations!\");\n\t newline();\n\t "
    " std::cin.get();\n\t return 0;\n\t }\n";
	return 0;}
int tCG::p04(){ //     PROG -> DEFS CALCS
	S1->obj += "int main(){\n" + S2->obj
	+ "std::cin.get();\n\t return 0;\n\t }\n";
	return 0;}
int tCG::p05(){ //        E -> $id
 	S1->obj = decor(S1->name);
	return 0;}
int tCG::p06(){ //        E -> $int
	S1->obj = S1->name + ".";
	return 0;}
int tCG::p07(){ //        E -> $dec
	S1->obj = S1->name;
	return 0;}
int tCG::p08(){ //        E -> AREX
	return 0;}
int tCG::p09(){ //        E -> COND
	return 0;}
int tCG::p10(){ //        E -> EASYLET
	return 0;}
int tCG::p11(){ //        E -> CPROC
	return 0;}
int tCG::p12(){ //     AREX -> HAREX E )
	if(S1->count == 0 && (S1->name == "/" || S1->name == "*"))
		S1->obj += "1.";
	S1->obj += S1->name + S2->obj + ")";
	return 0;}
int tCG::p13(){ //    HAREX -> ( AROP
	S1->obj = "(";
	S1->name = S2->name;
	S1->count = 0;
	return 0;}
int tCG::p14(){ //    HAREX -> HAREX E
	if(S1->count)
		S1->obj += S1->name;
	S1->obj += S2->obj;
	(S1->count)++;
	return 0;}
int tCG::p15(){ //     AROP -> +
	S1->obj = "+";
	return 0;}
int tCG::p16(){ //     AROP -> -
	S1->obj = "-";
	return 0;}
int tCG::p17(){ //     AROP -> *
	S1->obj = "*";
	return 0;}
int tCG::p18(){ //     AROP -> /
	S1->obj = "/";
	return 0;}
int tCG::p19(){ //  EASYLET -> HEASYL E )
	S1->obj += S2->obj + ")\n";
	return 0;}
int tCG::p20(){ //   HEASYL -> ( let ( )
	S1->obj = "(\n ";
	return 0;}
int tCG::p21(){ //   HEASYL -> HEASYL INTER
	S1->obj += S2->obj + ",\n\t ";
	return 0;}
int tCG::p22(){ //     COND -> ( cond BRANCHES )
	S1->obj = S3->obj;
	return 0;}
int tCG::p23(){ // BRANCHES -> CLAUS ELSE
	S1->obj += "\n\t:(" +S2->obj + ")";
	return 0;}
int tCG::p24(){ //    CLAUS -> ( BOOL E )
	S1->obj += S2->obj + "\n\t? " + S3->obj;
	return 0;}
int tCG::p25(){ //     ELSE -> ( else ELSEB )
	S1->obj += S3->obj;
	return 0;}
int tCG::p26(){ //    ELSEB -> E
	return 0;}
int tCG::p27(){ //    ELSEB -> INTER ELSEB
	S1->obj += ", " + S2->obj;
	return 0;}
int tCG::p28(){ //      STR -> $str
	S1->obj = S1->name;
	return 0;}
int tCG::p29(){ //      STR -> SCOND
	return 0;}
int tCG::p30(){ //    SCOND -> ( cond SBRANCHES )
	S1->obj = S3->obj;
	return 0;}
int tCG::p31(){ //SBRANCHES -> SELSE
	return 0;}
int tCG::p32(){ //SBRANCHES -> SCLAUS SBRANCHES
	S1->obj += "\n\t: " + S2->obj;
	return 0;}
int tCG::p33(){ //   SCLAUS -> ( BOOL STR )
	S1->obj += S2->obj + "\n\t? " + S3->obj;
	return 0;}
int tCG::p34(){ //    SELSE -> ( else STR )
	S1->obj += S3->obj;
	return 0;}
int tCG::p35(){ //    CPROC -> HCPROC )
	if(S1->count > 1)
		S1->obj += ")\n\t ";
	else
		S1->obj += ")";
	return 0;}
int tCG::p36(){ //   HCPROC -> ( $id
	S1->obj += decor(S2->name) + S1->name;
	S1->count = 0;
	return 0;}
int tCG::p37(){ //   HCPROC -> HCPROC E
	if(S1->count)
		S1->obj += "\n\t , ";
	S1->obj += S2->obj;
	(S1->count)++;
	return 0;}
int tCG::p38(){ //     BOOL -> $bool
	S1->obj = (S1->name == "#t") ? "true" : "false";
	return 0;}
int tCG::p39(){ //     BOOL -> $idq
	S1->obj = decor(S1->name);
	return 0;}
int tCG::p40(){ //     BOOL -> REL
	return 0;}
int tCG::p41(){ //     BOOL -> ( not BOOL )
	S1->obj = (S3->obj == "true") ? "false" : "true";
	return 0;}
int tCG::p42(){ //     BOOL -> CPRED
	return 0;}
int tCG::p43(){ //    CPRED -> HCPRED )
	S1->obj += ")";
	return 0;}
int tCG::p44(){ //   HCPRED -> ( $idq
	S1->obj += decor(S2->name) + "(";
	S1->count = 0;
	return 0;}
int tCG::p45(){ //   HCPRED -> HCPRED ARG
	if(S1->count)
		S1->obj += "\n\t , ";
	S1->obj += S2->obj;
	(S1->count)++;
	return 0;}
int tCG::p46(){ //      ARG -> E
	return 0;}
int tCG::p47(){ //      ARG -> BOOL
	return 0;}
int tCG::p48(){ //      REL -> ( = E E )
	S1->obj = "(" + S3->obj + " == " + S4->obj + ")"; 
	return 0;}
int tCG::p49(){ //      REL -> ( < E E )
	S1->obj = "(" + S3->obj + " " + S2->name + " " + S4->obj + ")"; 
	return 0;}
int tCG::p50(){ //      SET -> HSET E )
	S1->obj += " = " + S2->obj;
	return 0;}
int tCG::p51(){ //     HSET -> ( set! $id
	S1->obj += decor(S3->name);
	return 0;}
int tCG::p52(){ //  DISPSET -> ( display E )
	S1->obj = "display(" + S3->obj + ")";
	return 0;}
int tCG::p53(){ //  DISPSET -> ( display BOOL )
	S1->obj = "display(" + S3->obj + ")";  
	return 0;}
int tCG::p54(){ //  DISPSET -> ( display STR )
	S1->obj = "display(" + S3->obj + ")";  
	return 0;}
int tCG::p55(){ //  DISPSET -> ( newline )
	S1->obj = "newline()";
	return 0;}
int tCG::p56(){ //  DISPSET -> SET
	return 0;}
int tCG::p57(){ //    INTER -> DISPSET
	return 0;}
int tCG::p58(){ //    INTER -> E
	return 0;}
int tCG::p59(){ //    CALCS -> CALC
	S1->obj += ";\n\t ";
	return 0;}
int tCG::p60(){ //    CALCS -> CALCS CALC
	S1->obj += S2->obj + ";\n\t ";
	return 0;}
int tCG::p61(){ //     CALC -> E
 	S1->obj = "display(" + S1->obj + ");\n\t newline()";
	return 0;}
int tCG::p62(){ //     CALC -> BOOL
	return 0;}
int tCG::p63(){ //     CALC -> STR
	return 0;}
int tCG::p64(){ //     CALC -> DISPSET
	return 0;}
int tCG::p65(){ //     DEFS -> DEF
	return 0;}
int tCG::p66(){ //     DEFS -> DEFS DEF
	S1->obj += S2->obj;
	return 0;}
int tCG::p67(){ //      DEF -> PRED
	return 0;}
int tCG::p68(){ //      DEF -> VAR
	return 0;}
int tCG::p69(){ //      DEF -> PROC
	return 0;}
int tCG::p70(){ //     PRED -> HPRED BOOL )
	S1->obj += "return\n " + S2->obj + ";\n\t }\n";
	return 0;}
int tCG::p71(){ //    HPRED -> PDPAR )
	S1->obj += ")";
	declarations += S1->obj + ";\n";
	S1->obj += "{\n ";
	return 0;}
int tCG::p72(){ //    PDPAR -> ( define ( $idq
	S1->obj = "bool " + decor(S4->name) +"/*" + S4->line + "*/" + "(";
	S1->count = 0;
	return 0;}
int tCG::p73(){ //    PDPAR -> PDPAR $idq
	if(S1->count)
		S1->obj += S1->count%2 ? ", " : "\n\t , ";
	S1->obj += "bool " + decor(S2->name);
	(S1->count)++;
	return 0;}
int tCG::p74(){ //    PDPAR -> PDPAR $id
	if(S1->count)
		S1->obj += S1->count%2 ? ", " : "\n\t , ";
	S1->obj += "double " + decor(S2->name);
	(S1->count)++;
	return 0;}
int tCG::p75(){ //      VAR -> VARDCL E )
	S1->obj = "double " + S1->obj + " = " + S2->obj + ";\n";
	return 0;}
int tCG::p76(){ //   VARDCL -> ( define $id
	S1->obj = decor(S3->name) + "/*" + S3->line + "*/";
	declarations += "extern double " + S1->obj + ";\n";
	return 0;}
int tCG::p77(){ //     PROC -> HPROC BLOCK )
	S1->obj += S2->obj + "}\n";
	return 0;}
int tCG::p78(){ //     PROC -> HPROC E )
	S1->obj += "return\n " + S2->obj + ";\n\t }\n";
	return 0;}
int tCG::p79(){ //    HPROC -> PCPAR )
	S1->obj += S2->name;
	declarations += S1->obj + ";\n"; //!!!
 	S1->obj += "{\n ";
	return 0;}
int tCG::p80(){ //    HPROC -> HPROC INTER
	S1->obj += S2->obj + ";\n\t";
	return 0;}
int tCG::p81(){ //    PCPAR -> ( define ( $id
	S1->obj =  "double " + decor(S4->name) +
	"/*" + S4->line + "*/ (";
	S1->count = 0;
	S1->name = S4->name;
	return 0;}
int tCG::p82(){ //    PCPAR -> PCPAR $id
	if(S1->count)
		S1->obj += S1->count%2 ? ", " : "\n\t , ";
	S1->obj += "double " + decor(S2->name);
	++(S1->count);
	return 0;}
int tCG::p83(){ //    BLOCK -> HBLOCK E )
	S1->obj += "return\n " + S2->obj + ";\n\t}\n";
	return 0;}
int tCG::p84(){ //   HBLOCK -> BLVAR )
	return 0;}
int tCG::p85(){ //   HBLOCK -> HBLOCK INTER
	S1->obj += S2->obj + ";\n\t ";
	return 0;}
int tCG::p86(){ //    BLVAR -> ( let ( LOCDEF
	S1->obj = "{\n " + S4->obj;
	return 0;}
int tCG::p87(){ //    BLVAR -> BLVAR LOCDEF
	S1->obj += S2->obj;
	return 0;}
int tCG::p88(){ //   LOCDEF -> ( $id E )
	S1->obj = "double " + decor(S2->name) + "(" + S3->obj + ");\n\t ";
	return 0;}
//_____________________
int tCG::p89(){return 0;} int tCG::p90(){return 0;} 
int tCG::p91(){return 0;} int tCG::p92(){return 0;} 
int tCG::p93(){return 0;} int tCG::p94(){return 0;} 
int tCG::p95(){return 0;} int tCG::p96(){return 0;} 
int tCG::p97(){return 0;} int tCG::p98(){return 0;} 
int tCG::p99(){return 0;} int tCG::p100(){return 0;} 
int tCG::p101(){return 0;} int tCG::p102(){return 0;} 
int tCG::p103(){return 0;} int tCG::p104(){return 0;} 
int tCG::p105(){return 0;} int tCG::p106(){return 0;} 
int tCG::p107(){return 0;} int tCG::p108(){return 0;} 
int tCG::p109(){return 0;} int tCG::p110(){return 0;} 


