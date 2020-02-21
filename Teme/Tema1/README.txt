		>> TEMA 1 << 
		    EGC

	    Cernea David Andreas


	Implementare : 
	- bird -> createBird de tip Mesh formata din ochi (patrat),
		cioc (triunghiuri), picioare (doua cercuri, se instantiaza diferit
		- createCircle);
	- pipes -> 3 la numar, se respawneaza atunci cand trec de coordonata 0 de pe OX
		cu latura din dreapta;
		-> au fost realizate cu varfuri si indecsi, la fel ca bird, iar gap-urile
		sunt unice pentru fiecare pipe(se foloseste offsetY);

	In Update a fost realizata toata mecanica jocului: 

	Primul pas - se verifica daca jocul s-a incheiat(pasarea a intrat in vreun pipe) se
		se afiseaza scorul pe consola si se face ecranul negru;
	Altfel, se continua jocul astfel :
		- se translateaza pasarea catre pozitia initiala (bird_pos_x, bird_pos_y);
		- jocul trebuie sa inceapa; am folosit prima apasare a tastei Space ca un
		Start Game, lasand pipe-urile sa se spawneze; daca nu se apasa Space jocul
		este intr-o stare de freeze;
		- se verifica daca pasarea cade sau zboara si dam update la caracteristica de
		miscare pe OY folosind doua constante gravity si flaping si la caracteristica
		de rotatie; valorile au fost alese prin incercari repetate;
		- modificam matricea de translatie;
		- daca se iese din ecran cand se fac update-urile, se reseteaza gravitatia;
		- impunem limite unghiurilor de rotatie a.i. pasarea sa nu se roteasca incontinuu;
		- modificam matricea de rotatie;
		- daca se iese din ecran la translatie, modifcam pozitia y a pasarii 0, daca iese pe jos,
		resolution.y - lungimea corpului, daca iese pe sus;
		- randam pasarea;
		- miscam tuburile;
	Se trateaza coliziunile astfel : 
		- pasarea este incadrata intr-un cerc;
		- in functie de tubul care ajunge la pozitia pasarii (tubul 0, 1 sau 2) se verifica daca
		oricare din punctele de pe cerc nu se afla in interiorul tubului;
		- daca aceasta conditie nu este indeplinita se modifca variabila endGame = true; cand se intra
		din nou in functia Update jocul va sti ca a luat sfarsit si va afisa scorul;
		- mai departe verificam daca punctul din stanga-jos al pasarei a trecut de latura din dreapta a tubului
		- daca da, se incrementeaza scorul, iar in vectorul tubesScores cu elemente de tip bool notificam faptul
		ca scorul trecerii de tubul x a fost luat in evidenta. <tubesScores[x] = true>
		- daca un anumit tub apuca sa se respawneze se intervine asupra vectorului tubesScores,
		astfel incat sa putem sa obtinem scor din nou atunci cand trecem de acel tub;
		- verificam daca un tub a iesit prin stanga din ecran; daca da, se respawneaza in dreapta;
		- randeaza tuburile;

	Dificultate marita (bonus):
		- viteza de deplasare a tuburilor este marita cu coeficientul velocityFactor la fiecare 7 tuburi trecute