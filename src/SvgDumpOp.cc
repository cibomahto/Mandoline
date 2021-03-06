//
//  SVGDumpOperation.m
//  Mandoline
//
//  Created by GM on 11/24/10.
//  Copyright 2010 Belfry DevWorks. All rights reserved.
//

#include <fstream>
#include "SvgDumpOp.h"
#include "BGL/BGL.h"
#include "SlicingContext.h"
#include "CarvedSlice.h"

using namespace BGL;


SvgDumpOp::~SvgDumpOp()
{
}



void SvgDumpOp::main()
{
    if ( isCancelled ) return;
    if ( NULL == context ) return;
    if ( NULL == slice ) return;

    float extrusionWidth = context->standardExtrusionWidth();
    char dumpFileName[512];
    snprintf(dumpFileName, sizeof(dumpFileName), "%.128s-%06.2f.svg", context->dumpPrefix.c_str(), zLayer);

    fstream fout;
    fout.open(dumpFileName, fstream::out | fstream::trunc);
    if (!fout.good()) {
        return;
    }
    slice->svgPathWithSizeAndOffset(fout, context->svgWidth, context->svgHeight, context->svgXOff, context->svgYOff, extrusionWidth);
    fout.close();

    if ( isCancelled ) return;
}


