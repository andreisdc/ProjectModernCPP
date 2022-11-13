#include <iostream>
#include "County.hpp"
#include "Board.hpp"

int main() {
	County Alba("Alba", 1);
	County Arad("Arad", 1);
	County Arges("Arges", 1);
	County Bacau("Bacau", 1);
	County Bihor("Bihor", 1);
	County Bistrita_Nasaud("Bistrita-Nasaud", 1);
	County Botosani("Botosani", 1);
	County Brasov("Brasov", 1);
	County Braila("Braila", 1);
	County Bucuresti("Bucuresti", 1);
	County Buzau("Buzau", 1);
	County Caras_Severin("Caras-Severin", 1);
	County Calarasi("Calarasi", 1);
	County Cluj("Cluj", 1);
	County Constanta("Constanta", 1);
	County Covasna("Covasna", 1);
	County Dambovita("Dambovita", 1);
	County Dolj("Dolj", 1);
	County Galati("Galati", 1);
	County Giurgiu("Giurgiu", 1);
	County Gorj("Gorj", 1);
	County Harghita("Harghita", 1);
	County Hunedoara("Hunedoara", 1);
	County Ialomita("Ialomita", 1);
	County Iasi("Iasi", 1);
	County Ilfov("Ilfov", 1);
	County Maramures("Maramures", 1);
	County Mehedinti("Mehedinti", 1);
	County Mures("Mures", 1);
	County Neamt("Neamt", 1);
	County Olt("Olt", 1);
	County Prahova("Prahova", 1);
	County Satu_Mare("Satu Mare", 1);
	County Salaj("Salaj", 1);
	County Sibiu("Sibiu", 1);
	County Suceava("Suceava", 1);
	County Teleorman("Teleorman", 1);
	County Timis("Timis", 1);
	County Tulcea("Tulcea", 1);
	County Vaslui("Vaslui", 1);
	County Valcea("Valcea", 1);
	County Vrancea("Vrancea", 1);

	Alba.addCounty(&Mures);
	Alba.addCounty(&Sibiu);
	Alba.addCounty(&Valcea);
	Alba.addCounty(&Hunedoara);
	Alba.addCounty(&Arad);
	Alba.addCounty(&Bihor);
	Alba.addCounty(&Cluj);

	Arad.addCounty(&Timis);
	Arad.addCounty(&Hunedoara);
	Arad.addCounty(&Alba);
	Arad.addCounty(&Bihor);

	Arges.addCounty(&Brasov);
	Arges.addCounty(&Dambovita);
	Arges.addCounty(&Teleorman);
	Arges.addCounty(&Olt);
	Arges.addCounty(&Valcea);
	Arges.addCounty(&Sibiu);

	Bacau.addCounty(&Neamt);
	Bacau.addCounty(&Vaslui);
	Bacau.addCounty(&Vrancea);
	Bacau.addCounty(&Covasna);
	Bacau.addCounty(&Harghita);

	Bihor.addCounty(&Satu_Mare);
	Bihor.addCounty(&Salaj);
	Bihor.addCounty(&Cluj);
	Bihor.addCounty(&Alba);
	Bihor.addCounty(&Arad);

	Bistrita_Nasaud.addCounty(&Suceava);
	Bistrita_Nasaud.addCounty(&Maramures);
	Bistrita_Nasaud.addCounty(&Mures);
	Bistrita_Nasaud.addCounty(&Cluj);

	Botosani.addCounty(&Suceava);
	Botosani.addCounty(&Iasi);

	Brasov.addCounty(&Dambovita);
	Brasov.addCounty(&Arges);
	Brasov.addCounty(&Sibiu);
	Brasov.addCounty(&Mures);
	Brasov.addCounty(&Harghita);
	Brasov.addCounty(&Covasna);
	Brasov.addCounty(&Buzau);
	Brasov.addCounty(&Prahova);

	Braila.addCounty(&Tulcea);
	Braila.addCounty(&Constanta);
	Braila.addCounty(&Ialomita);
	Braila.addCounty(&Buzau);
	Braila.addCounty(&Vrancea);
	Braila.addCounty(&Galati);

	Bucuresti.addCounty(&Ilfov);

	Buzau.addCounty(&Braila);
	Buzau.addCounty(&Ialomita);
	Buzau.addCounty(&Prahova);
	Buzau.addCounty(&Braila);
	Buzau.addCounty(&Covasna);
	Buzau.addCounty(&Vrancea);

	Caras_Severin.addCounty(&Timis);
	Caras_Severin.addCounty(&Hunedoara);
	Caras_Severin.addCounty(&Gorj);
	Caras_Severin.addCounty(&Mehedinti);

	Calarasi.addCounty(&Giurgiu);
	Calarasi.addCounty(&Ilfov);
	Calarasi.addCounty(&Constanta);
	Calarasi.addCounty(&Ialomita);

	Cluj.addCounty(&Alba);
	Cluj.addCounty(&Mures);
	Cluj.addCounty(&Bistrita_Nasaud);
	Cluj.addCounty(&Salaj);
	Cluj.addCounty(&Maramures);
	Cluj.addCounty(&Bihor);

	Constanta.addCounty(&Tulcea);
	Constanta.addCounty(&Calarasi);
	Constanta.addCounty(&Ialomita);
	Constanta.addCounty(&Braila);

	Covasna.addCounty(&Brasov);
	Covasna.addCounty(&Harghita);
	Covasna.addCounty(&Bacau);
	Covasna.addCounty(&Vrancea);
	Covasna.addCounty(&Buzau);

	Dambovita.addCounty(&Arges);
	Dambovita.addCounty(&Prahova);
	Dambovita.addCounty(&Ilfov);
	Dambovita.addCounty(&Giurgiu);
	Dambovita.addCounty(&Teleorman);
	Dambovita.addCounty(&Brasov);

	Dolj.addCounty(&Mehedinti);
	Dolj.addCounty(&Gorj);
	Dolj.addCounty(&Valcea);
	Dolj.addCounty(&Olt);

	Galati.addCounty(&Vrancea);
	Galati.addCounty(&Braila);
	Galati.addCounty(&Tulcea);
	Galati.addCounty(&Vaslui);

	Giurgiu.addCounty(&Ilfov);
	Giurgiu.addCounty(&Calarasi);
	Giurgiu.addCounty(&Dambovita);
	Giurgiu.addCounty(&Teleorman);

	Gorj.addCounty(&Hunedoara);
	Gorj.addCounty(&Valcea);
	Gorj.addCounty(&Dolj);
	Gorj.addCounty(&Mehedinti);
	Gorj.addCounty(&Caras_Severin);

	Harghita.addCounty(&Mures);
	Harghita.addCounty(&Brasov);
	Harghita.addCounty(&Covasna);
	Harghita.addCounty(&Bacau);
	Harghita.addCounty(&Neamt);
	Harghita.addCounty(&Suceava);

	Hunedoara.addCounty(&Alba);
	Hunedoara.addCounty(&Valcea);
	Hunedoara.addCounty(&Gorj);
	Hunedoara.addCounty(&Caras_Severin);
	Hunedoara.addCounty(&Timis);
	Hunedoara.addCounty(&Arad);

	Ialomita.addCounty(&Braila);
	Ialomita.addCounty(&Constanta);
	Ialomita.addCounty(&Calarasi);
	Ialomita.addCounty(&Ilfov);
	Ialomita.addCounty(&Prahova);
	Ialomita.addCounty(&Buzau);

	Iasi.addCounty(&Botosani);
	Iasi.addCounty(&Suceava);
	Iasi.addCounty(&Neamt);
	Iasi.addCounty(&Vaslui);

	Ilfov.addCounty(&Prahova);
	Ilfov.addCounty(&Ialomita);
	Ilfov.addCounty(&Calarasi);
	Ilfov.addCounty(&Giurgiu);
	Ilfov.addCounty(&Dambovita);

	Maramures.addCounty(&Satu_Mare);
	Maramures.addCounty(&Salaj);
	Maramures.addCounty(&Cluj);
	Maramures.addCounty(&Bistrita_Nasaud);
	Maramures.addCounty(&Suceava);

	Mehedinti.addCounty(&Caras_Severin);
	Mehedinti.addCounty(&Gorj);
	Mehedinti.addCounty(&Dolj);

	Mures.addCounty(&Bistrita_Nasaud);
	Mures.addCounty(&Suceava);
	Mures.addCounty(&Harghita);
	Mures.addCounty(&Brasov);
	Mures.addCounty(&Sibiu);
	Mures.addCounty(&Alba);
	Mures.addCounty(&Cluj);

	Neamt.addCounty(&Suceava);
	Neamt.addCounty(&Iasi);
	Neamt.addCounty(&Valcea);
	Neamt.addCounty(&Bacau);
	Neamt.addCounty(&Harghita);

	Olt.addCounty(&Dolj);
	Olt.addCounty(&Valcea);
	Olt.addCounty(&Arges);
	Olt.addCounty(&Teleorman);

	Prahova.addCounty(&Brasov);
	Prahova.addCounty(&Buzau);
	Prahova.addCounty(&Ialomita);
	Prahova.addCounty(&Ilfov);
	Prahova.addCounty(&Dambovita);

	Satu_Mare.addCounty(&Bihor);
	Satu_Mare.addCounty(&Salaj);
	Satu_Mare.addCounty(&Maramures);

	Salaj.addCounty(&Bihor);
	Salaj.addCounty(&Cluj);
	Salaj.addCounty(&Maramures);
	Salaj.addCounty(&Satu_Mare);

	Sibiu.addCounty(&Alba);
	Sibiu.addCounty(&Mures);
	Sibiu.addCounty(&Brasov);
	Sibiu.addCounty(&Arges);
	Sibiu.addCounty(&Valcea);

	Suceava.addCounty(&Maramures);
	Suceava.addCounty(&Bistrita_Nasaud);
	Suceava.addCounty(&Mures);
	Suceava.addCounty(&Harghita);
	Suceava.addCounty(&Neamt);
	Suceava.addCounty(&Iasi);
	Suceava.addCounty(&Botosani);

	Teleorman.addCounty(&Olt);
	Teleorman.addCounty(&Arges);
	Teleorman.addCounty(&Dambovita);
	Teleorman.addCounty(&Giurgiu);

	Timis.addCounty(&Arad);
	Timis.addCounty(&Hunedoara);
	Timis.addCounty(&Caras_Severin);

	Tulcea.addCounty(&Galati);
	Tulcea.addCounty(&Braila);
	Tulcea.addCounty(&Constanta);

	Vaslui.addCounty(&Iasi);
	Vaslui.addCounty(&Neamt);
	Vaslui.addCounty(&Bacau);
	Vaslui.addCounty(&Vrancea);
	Vaslui.addCounty(&Galati);

	Valcea.addCounty(&Sibiu);
	Valcea.addCounty(&Arges);
	Valcea.addCounty(&Olt);
	Valcea.addCounty(&Dolj);
	Valcea.addCounty(&Gorj);
	Valcea.addCounty(&Hunedoara);
	Valcea.addCounty(&Alba);

	Vrancea.addCounty(&Bacau);
	Vrancea.addCounty(&Vaslui);
	Vrancea.addCounty(&Galati);
	Vrancea.addCounty(&Braila);
	Vrancea.addCounty(&Buzau);
	Vrancea.addCounty(&Covasna);

	Board board;

	board.addCounty(Alba);
	board.addCounty(Arad);
	board.addCounty(Arges);
	board.addCounty(Bacau);
	board.addCounty(Bihor);
	board.addCounty(Bistrita_Nasaud);
	board.addCounty(Botosani);
	board.addCounty(Brasov);
	board.addCounty(Braila);
	board.addCounty(Bucuresti);
	board.addCounty(Buzau);
	board.addCounty(Caras_Severin);
	board.addCounty(Calarasi);
	board.addCounty(Cluj);
	board.addCounty(Constanta);
	board.addCounty(Covasna);
	board.addCounty(Dambovita);
	board.addCounty(Dolj);
	board.addCounty(Galati);
	board.addCounty(Giurgiu);
	board.addCounty(Gorj);
	board.addCounty(Harghita);
	board.addCounty(Hunedoara);
	board.addCounty(Ialomita);
	board.addCounty(Iasi);
	board.addCounty(Ilfov);
	board.addCounty(Maramures);
	board.addCounty(Mehedinti);
	board.addCounty(Mures);
	board.addCounty(Neamt);
	board.addCounty(Olt);
	board.addCounty(Prahova);
	board.addCounty(Satu_Mare);
	board.addCounty(Salaj);
	board.addCounty(Sibiu);
	board.addCounty(Suceava);
	board.addCounty(Teleorman);
	board.addCounty(Timis);
	board.addCounty(Tulcea);
	board.addCounty(Vaslui);
	board.addCounty(Valcea);
	board.addCounty(Vrancea);

	board.selectCounty();
	board.showCounty();
	board.moveCounty();
	board.showCounty();
	board.moveCounty();
	board.showCounty();
	board.moveCounty();
	board.showCounty();

	return 0;
}
