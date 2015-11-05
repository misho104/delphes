
#include "classes/DelphesFormula.h"

#include "TString.h"

#include <stdexcept>

using namespace std;

//------------------------------------------------------------------------------

DelphesFormula::DelphesFormula() :
  TFormula()
{
}

//------------------------------------------------------------------------------

DelphesFormula::DelphesFormula(const char *name, const char *expression) :
  TFormula()
{
}

//------------------------------------------------------------------------------

DelphesFormula::~DelphesFormula()
{
}

//------------------------------------------------------------------------------

Int_t DelphesFormula::Compile(const char *expression)
{
  TString buffer;
  const char *it;
  for(it = expression; *it; ++it)
  {
    if(*it == ' ' || *it == '\t' || *it == '\r' || *it == '\n' || *it == '\\' ) continue;
    buffer.Append(*it);
  }
  buffer.ReplaceAll("pt", "x");
  buffer.ReplaceAll("eta", "y");
  buffer.ReplaceAll("phi", "z");
  buffer.ReplaceAll("energy", "t");
  if(TFormula::Compile(buffer) != 0)
  {
    throw runtime_error("Invalid formula.");
  }
  return 0;
}

//------------------------------------------------------------------------------

Double_t DelphesFormula::Eval(Double_t pt, Double_t eta, Double_t phi, Double_t energy)
{
   Double_t x[4] = {pt, eta, phi, energy};
   return EvalPar(x);
}

//------------------------------------------------------------------------------
