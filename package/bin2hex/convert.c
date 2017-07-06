/*
 * Convert.c
 *
 * Copyright (C) 2014 British Sky Broadcasting (BSkyB).
 *
 * This file converts binary to hex and output to a file in hex format.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Func        : Bin to Hex conversion 
 * input file  : Binary bile
 * Output file : Hex file
 */

int main ( int argc, char *argv[] )
{
    FILE *infile;
    FILE *outfile;
    int count=1;
    unsigned char buf[30];
    unsigned char read_byte;

    printf ( "converting the bin to hex\n" );

    if ( argc < 2 ) {
	printf ( "Usage: convert <input file> <output file>\n" );
	return 1;
    }

    infile = fopen ( argv[1], "r" );
    if ( !infile ) {
	printf ( "failed to open input file %s\n", argv[1] );
	return 1;
    }

    outfile = fopen ( argv[2], "wb" );
    if ( !outfile ) {
        printf ( "failed to open out file %s\n", argv[2] );
        return 1;
    }
    memset ( buf, 0x00, sizeof(buf) );
    sprintf ( buf, "unsigned char sky_fdt[]={\n" );
    fwrite ( buf, 26, 1, outfile );

    while ( !feof(infile) ) {

       memset ( buf, 0x00, sizeof(buf) );
       if (0 == (count % 17 )){
          if ( fread ( &read_byte, 1, 1, infile ) == 1 ) {
             sprintf ( buf, "\n0x%02x,", read_byte );
	     fwrite ( buf, 6, 1, outfile );
	     count = 1;
	     count ++;
	  }

       }
       else {
          if ( fread ( &read_byte, 1, 1, infile ) == 1 ) {
             sprintf ( buf, "0x%02x,", read_byte );
	     fwrite ( buf, 5, 1, outfile );
	     count ++;
	  }
       }

    }
    memset ( buf, 0x00, sizeof(buf) );
    sprintf ( buf, "\n};");
    fwrite ( buf, 3, 1, outfile );

    fclose ( infile );
    fclose ( outfile );

    return 0;
}
