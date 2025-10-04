/*
 *  disarm_test.c
 *  DisARM
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


void Disassemble(unsigned int *armI, int count, unsigned int startAddress);
void DecodeInstruction(unsigned int instr, char *decodeStr);
int ishexdigit(int c);

int main(int argc, const char * argv[])
{
	char line_buffer[512];
	char *ds = calloc(1,512);
    FILE *fp;
	char *p, *q;
	int addr;
	unsigned int val;

    if(argc < 2)
    {
        fprintf(stderr, "Usage: DisARM <filename>\n");
        return 1;
    }
    
    /* Open KMD file for reading */
    fp = fopen(argv[1], "r");

	while(!feof(fp))
	{
		fgets(line_buffer, 512, fp);
		
		if(line_buffer[0] == ':')
		{
			/* Symbol */
			continue;
		}
		else
		{
			/* skip white space */
			p = line_buffer;
			while(isspace(*p))
			{
				p++;
			};
			
			if(!*p)
			{
				/* skip blank lines */
				continue;
			}
			
			addr = (int)strtol(p, &q, 16);
			
			if((q-p) < 8 || *q != ':')
			{
				/* Invalid line */
				continue;
			}

			p = q + 1; /* skip colon */
			while(isspace(*p))
			{
				p++;
			};
			
			val = (int)strtol(p, &q, 16);

			if((q-p) < 8)
			{
				/* Not a 32-bit value so ignore */
				continue;
			}
			
			memset(ds, 0, 512);
			DecodeInstruction(val, ds);
			printf("%08x %08x %s\n", addr, val, ds);

			
			
		}
			
		
	}
    fclose(fp);
	free(ds);
    return 0;
}


