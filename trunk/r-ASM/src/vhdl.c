/* r-ASM | The r-VEX assembler/instruction memory generator
 *
 * Copyright (c) 2008, Thijs van As <t.vanas@gmail.com>
 *
 * Computer Engineering Laboratory
 * Delft University of Technology
 * Delft, The Netherlands
 * 
 * http://r-vex.googlecode.com
 * 
 * r-ASM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * vhdl.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "rasm.h"

/* prints vhdl header to file */
void vhdl_header(char *src_file, char *flags, char *dest_file)
{
	char date[30];
	size_t i;
	struct tm tim;
	time_t now;

	now = time(NULL);
	tim = *(localtime(&now));
	i = strftime(date, 30, "%b %d, %Y @ %H:%M:%S\n", &tim);


	fprintf(out_vhd, "\
--------------------------------------------------------------------------------\n\
-- r-VEX | Instruction ROM\n\
--------------------------------------------------------------------------------\n\
-- \n\
-- This file was assembled by r-ASM, the r-VEX assembler/\n\
-- instruction ROM generator.\n\
-- \n\
--     source file: %s\n\
--     r-ASM flags: %s\n\
--     date & time: %s\
-- \n\
-- r-VEX & r-ASM are\n\
-- Copyright (c) 2008, Thijs van As <t.vanas@gmail.com>\n\
-- \n\
-- Computer Engineering Laboratory\n\
-- Delft University of Technology\n\
-- Delft, The Netherlands\n\
-- \n\
-- http://r-vex.googlecode.com\n\
-- \n\
-- r-VEX is free hardware: you can redistribute it and/or modify\n\
-- it under the terms of the GNU General Public License as published by\n\
-- the Free Software Foundation, either version 3 of the License, or\n\
-- (at your option) any later version.\n\
-- \n\
-- This program is distributed in the hope that it will be useful,\n\
-- but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\
-- GNU General Public License for more details.\n\
-- \n\
-- You should have received a copy of the GNU General Public License\n\
-- along with this program.  If not, see <http://www.gnu.org/licenses/>.\n\
-- \n\
--------------------------------------------------------------------------------\n\
-- %s (generated by r-ASM)\n\
--------------------------------------------------------------------------------\n\
\n\
library ieee;\n\
use ieee.std_logic_1164.all;\n\
\n\
entity i_mem is\n\
\tport ( reset   : in std_logic;                        -- system reset\n\
\t       address : in std_logic_vector(7 downto 0);     -- address of instruction to be read\n\
\n\
\t       instr   : out std_logic_vector(127 downto 0)); -- instruction (4 syllables)\n\
end entity i_mem;\n\
\n\
\n\
architecture behavioural of i_mem is\n\
begin\n\
\tmemory : process(address, reset)\n\
\tbegin\n\
\t\tif (reset = '1') then\n\
\t\t\tinstr <= x\"00000000000000000000000000000000\";\n\
\t\telse\n\
\t\t\tcase address is\n", src_file, flags, date, dest_file);

} 

/* prints vhdl footer to file */
void vhdl_footer()
{
	char *footer = "\
\t\t\t\twhen others => instr <= \"00000000000000000000000000000010\"& -- nop\n\
\t\t\t\t                        \"00000000000000000000000000000000\"& -- nop\n\
\t\t\t\t                        \"00000000000000000000000000000000\"& -- nop\n\
\t\t\t\t                        \"00111110000000000000000000000001\"; -- stop\n\
\t\t\tend case;\n\
\t\tend if;\n\
\tend process memory;\n\
end architecture behavioural;\n\n\
";
	fprintf(out_vhd, footer);
}

