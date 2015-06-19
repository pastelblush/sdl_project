# sdl_project
SDL Projector With ADS

the plc variable needed to control is:
'''

	selectscreen : INT;   \\to select screen (0 for blank, 1 - 9 for texture, 6464 to quit)
	bitmapdone:BOOL;  \\ if bitmap has being shown ( signal might be late because of ads, use as ref only)
	recipewrite : BOOL; \\ to write a recipe
	recipedone:BOOL;\\ recipe write done



	bmp1 : STRING(80);  path to bitmap stored.
	bmp2 : STRING(80);
	bmp3 : STRING(80);
	bmp4 : STRING(80);
	bmp5 : STRING(80);
	bmp6 : STRING(80);
	bmp7 : STRING(80);
	bmp8 : STRING(80);
	bmp9 : STRING(80);

'''


run using cmd line or create a shortcut:
'''
	projectorc.exe <monitor_number 0 - etc > <adsportno> <prefix_for_variable>
'''


eg.

'''
projectorc.exe 1 801 main. :

	so the variable would linked to :
		main.selectscreen
		main.bitmapdone
		...etc


projectorc.exe 1 801 main.S2_ :

	so the variable would linked to :
		main.s2_selectscreen
		main.s2_bitmapdone
		...etc

projectorc.exe 2 801 gvl. :

	Port 851 of tc2
	display to screen 3 (0 would be your main display) 
	so the variable would linked to :
		gvl.selectscreen
		gvl.bitmapdone
		...etc
'''