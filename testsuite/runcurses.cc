/*---------------------------------------------------------------------\
|                                                                      |  
|                      __   __    ____ _____ ____                      |  
|                      \ \ / /_ _/ ___|_   _|___ \                     |  
|                       \ V / _` \___ \ | |   __) |                    |  
|                        | | (_| |___) || |  / __/                     |  
|                        |_|\__,_|____/ |_| |_____|                    |  
|                                                                      |  
|                               core system                            | 
|                                                        (C) SuSE GmbH |  
\----------------------------------------------------------------------/ 

   File:       runcurses.cc

   Author:     Klaus Kaempf (kkaempf@suse.de)
   Maintainer: Klaus Kaempf (kkaempf@suse.de)

/-*/
/*
#include <scr/run_agent.h>

#include "../src/LiloAgent.h"

int main (int argc, char *argv[])
{
    run_agent <LiloAgent>(argc, argv, true);
}
*/
#include <stdio.h>

#include "YNCursesUI.h"

#include <ycp/Parser.h>
#include "../src/YNCursesUI.h"
#include <ycp/y2log.h>

extern int yydebug;

int
main (int argc, char *argv[])
{
    const char *fname = 0;
    FILE *infile = stdin;

    if (argc > 1)
    {
	int argp = 1;
	while (argp < argc)
	{
	    if ((argv[argp][0] == '-')
	        && (argv[argp][1] == 'l')
	        && (argp+1 < argc))
	    {
		argp++;
		set_log_filename (argv[argp]);
	    }
	    else if (fname == 0)
	    {
		fname = argv[argp];
	    }
	    else
	    {
		fprintf (stderr, "Bad argument '%s'\nUsage: runcurses [ name.ycp ]\n", argv[argp]);
	    }
	    argp++;
	}
    }

    Parser *parser;
    parser = new Parser ();

    if (!parser)
    {
	fprintf (stderr, "Failed to create YCPParser\n");
	return 1;
    }

    YNCursesUI * ncurses_ui = new YNCursesUI(true, 0, 0, 0 );

    if (! ncurses_ui)
    {
	fprintf (stderr, "Failed to create Y2NCursesUI\n");
	delete parser;
	return 1;
    }

    if (fname != 0)
    {
	infile = fopen (fname, "r");
	if (infile == 0)
	{
	    fprintf (stderr, "Failed to open '%s'\n", fname);
	    return 1;
	}
    }
    else
    {
	fname = "stdin";
    }

    parser->setInput (infile, fname);
    parser->setBuffered();

    YCPValue value = YCPVoid();

    for (;;)
    {
	YCode* code = parser->parse();
	if (code == NULL)
	    break;

	YCPValue value = code->evaluate ();

	printf ("(%s)\n", value->toString().c_str());
    }

    delete ncurses_ui;
    delete parser;

    if (infile != stdin)
	fclose (infile);

    return 0;
}
