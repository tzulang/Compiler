#pragma once
 #include "Lexer/parsercombinatror.h"
#include "basicparsercombinators.h"


namespace Lexer {

    using namespace compiler;

    Parser pInteger = pOneOrMore(pDigit);

    Parser pFloat =  pConcat<strType>({
                                     pMaybe(pInteger),
                                     pDot,
                                     pInteger
                                    });

    Parser pReal = pOneOf<strType>({
                                    pMatchMax<strType>({
                                        pInteger,
                                        pMaybe<strType>(
                                            pConcat<strType>({ pDot, pInteger})
                                        )
                                    }),

                                    pConcat<strType>({ pDot, pInteger })
                                   });

    Parser pVar = pConcat<strType>({
                                       pOneOf<strType>({
                                           pUnderScore,
                                           pAlphaBet,
                                       }),
                                       pMany<strType>({
                                           pOneOf<strType>({
                                               pUnderScore,
                                               pAlphaBet,
                                               pDigit
                                           }),
                                       })
                                   });









}
