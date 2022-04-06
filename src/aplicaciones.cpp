/* 5286580 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/aplicaciones.h"
#include "../include/cadena.h"
#include "../include/iterador.h"

TCadena insertarAlFinal(nat natural, double real, TCadena cad)
{

  cad = insertarAlInicio(natural, real, cad);
  cad = cadenaSiguiente(cad);
  return cad;
}

TCadena removerPrimero(TCadena cad)
{

  cad = removerDeCadena(natInfo(primeroEnCadena(cad)), cad);
  return cad;
}

TCadena copiaCadena(TCadena cad)
{
  if (cad != NULL)
  {
    TCadena copia = crearCadena();
    TCadena partida = cad;
    TCadena siguiente = cad;
    TInfo info = primeroEnCadena(cad);
    copia = insertarAlFinal(natInfo(info), realInfo(info), copia);
    siguiente = cadenaSiguiente(siguiente);

    while (siguiente != partida)
    {
      TInfo info = primeroEnCadena(siguiente);
      copia = insertarAlFinal(natInfo(info), realInfo(info), copia);
      siguiente = cadenaSiguiente(siguiente);
    }
      return copia;
  }
  else
    return NULL;
}

TIterador reversoDeIterador(TIterador iter)
{
  TIterador reverso = crearIterador();

  reiniciarIterador(iter);
  reiniciarIterador(reverso);
  TCadena aux = crearCadena();
  int count = 0;
  while (estaDefinidaActual(iter))
  {
    nat entrante = actualEnIterador(iter);
    aux = insertarAlInicio(entrante, 0, aux);
    avanzarIterador(iter);
    count++;
  }

  for (int i = 0; i < count; i++)
  {
    agregarAIterador(natInfo(primeroEnCadena(aux)), reverso);
    aux = cadenaSiguiente(aux);
  }
  liberarCadena(aux);
  reiniciarIterador(reverso);

  return reverso;
}
