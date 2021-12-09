#include "Y21Day09.h"

Y21Day09::Y21Day09()
{

}


void Y21Day09::computFirstResult()
{
    Map inMap(_input);

    int riskCount = 0;
    for(int row =0 ; row < inMap._map.size() ; row++)
    {
        for(int column = 0 ; column < inMap._map[row].size() ; column++)
        {
            if(inMap.isLowPoint(row,column))
                riskCount += (inMap._map[row][column] + 1);

        }
    }
    fprintf(stdout, "Res for first part is %i\r\n", riskCount);
    fflush(stdout);
}


void Y21Day09::computSecondResult()
{
    fprintf(stdout, "Enter compute second\r\n");
    fflush(stdout);

    Map inMap(_input);

    QVector<Bassin> allBassins {};

    for(int row =0 ; row < inMap._map.size() ; row++)
    {
        for(int column = 0 ; column < inMap._map[row].size() ; column++)
        {
            if(inMap.isLowPoint(row,column))
            {
//                fprintf(stdout, "Find a low point at [%i][%i]\r\n", row, column);
//                fflush(stdout);

                Point lowPoint; lowPoint.x = column; lowPoint.y = row; lowPoint.value = inMap._map[row][column];
                Bassin bass; bass.points = {}; bass.points.push_back(lowPoint);
                inMap.expandBassin(bass.points, bass);
                allBassins.push_back(bass);

                fprintf(stdout, "New bass starting at [%i][%i] of size %i\r\n", row, column, bass.points.size());
                fflush(stdout);
            }

        }
    }

    std::sort(allBassins.begin(), allBassins.end(), [](Bassin a, Bassin b) {return a.points.size() < b.points.size();});

    int basNbr = allBassins.size();

    fprintf(stdout, "Max  bass size are %i, %i and %i\r\n", allBassins[basNbr-1].points.size(), allBassins[basNbr-2].points.size(), allBassins[basNbr-3].points.size());
    fflush(stdout);

    fprintf(stdout, "Res for second part %i\r\n", allBassins[basNbr-1].points.size() * allBassins[basNbr-2].points.size() * allBassins[basNbr-3].points.size());
    fflush(stdout);
}


Map::Map(const QVector<QString> input)
{
    _map = QVector<QVector<int>>({});

    for(int row = 0 ; row < input.size() ; row++)
    {
        QVector<int> line = {};
        for(int column = 0 ; column < input[row].size() ; column++)
        {
            line.push_back(input[row][column].digitValue());
        }
        _map.push_back(line);
    }
}


QVector<Point> Map::getNeighbourg(int row, int column, bool withDiago) const
{
    QVector<Point> res = {};

    if(row > 0)
        res.push_back(newPoint(row-1, column));
    if(row < (_map.size() -1))
        res.push_back(newPoint(row+1, column));
    if(column > 0)
        res.push_back(newPoint(row, column-1));
    if(column < _map[row].size()-1)
        res.push_back(newPoint(row, column+1));
    if(withDiago)
    {
        if((row > 0) && (column > 0))
            res.push_back(newPoint(row -1 ,column -1));
        if((row > 0) && (column < _map[row].size()-1))
            res.push_back(newPoint(row-1, column +1));
        if((row < (_map.size() -1)) && column > 0)
            res.push_back(newPoint(row + 1, column - 1));
        if((row < (_map.size() -1)) && (column < _map[row].size()-1))
            res.push_back(newPoint(row + 1, column + 1));
    }

    return res;
}


bool Map::coorOk(QPair<int,int> dir) const
{
    bool upOk = (dir.first >= 0);
    bool leftOk = (dir.second >= 0);
    bool downOk = (dir.first < _map.size());
    bool rightOk = ((upOk && downOk) ? (dir.second < _map[dir.first].size()) : false); //Protect out of bound for _map[dir.first]

    return (upOk && leftOk && downOk && rightOk);
}


bool Map::isLowPoint(int row, int column)
{
    bool res = true;
//    QVector<Point> neighborhood = getNeighbourg(row, column);
    for(Point neigbhbor : getNeighbourg(row, column))
    {
        int value = neigbhbor.value;
        if(_map[row][column] > value)
        {
            res = false;
            break;
        }
    }
    return res;
}

bool Map::isLowPointOfStranger(const Point& pt, const Bassin &bass)
{

    bool res = true;
//    QVector<Point> neighborhood = getNeighbourg(row, column);
    for(Point neigbhbor : getNeighbourg(pt.y, pt.x))
    {
        if(pt.y == 1 && pt.x == 2)
        {
//            fprintf(stdout, "    BreakPoint\r\n");
//            fflush(stdout);
        }
        if(isInBassin(neigbhbor, bass))
            continue;
        int value = neigbhbor.value;
        if(pt.value > value)
        {

            res = false;
            break;
        }
    }
    return res;
}

bool Map::isInBassin(Point pt, const Bassin &bas)
{
    for(Point bPt : bas.points)
    {
        if((pt.x == bPt.x) && (pt.y == bPt.y))
        {
            return true;
        }
    }
    return false;
}

void Map::expandBassin(QVector<Point> lowPoints, Bassin& bass)
{
    QVector<Point> newLowPoint = {};
    for(Point lowPt : lowPoints)
    {
        for(Point neighbor : getNeighbourg(lowPt.y,lowPt.x))
        {
            if(isInBassin(neighbor,bass))
                continue;
            else if((neighbor.value != 9) && isLowPointOfStranger(neighbor, bass))
            {
                newLowPoint.push_back(neighbor);
                bass.points.push_back(neighbor);
                continue; //TRVD add to log
            }
            else
            {
//                fprintf(stdout, "Do not add _map[%i][%i]=%i, neighbor of _map[%i][%i]=%i\r\n", neighbor.y, neighbor.x, neighbor.value, lowPt.y, lowPt.x, lowPt.value);
//                fflush(stdout);
            }

        }
    }
    if(newLowPoint.size() > 0 )
    {
        expandBassin(newLowPoint, bass);
    }
    else
    {
        return;
    }
}


Point Map::newPoint(int row, int column) const
{
    Point res;
    res.x = column;
    res.y = row;
    res.value = _map[row][column];
    return res;
}



void Map::print()
{
    for(int row = 0 ; row < _map.size() ; row++)
    {
        for(int column = 0 ; column < _map[row].size() ; column++)
        {
            fprintf(stdout, "%i", (_map[row][column]));
        }
        fprintf(stdout, "\r\n");
    }
    fflush(stdout);
}


//exemple input =>
/*Res first part = 15
///*Res second part = 1134
const QVector<QString> Y21Day09::_input = {
    "2199943210",
    "3987894921",
    "9856789892",
    "8767896789",
    "9899965678"
};
// */

// /*
// Res first part 475
// Res second  part 1092012
const QVector<QString> Y21Day09::_input = {
    "9987632123989012498765323467892101296546544569898545696545976534567987789212976789887578878998765432",
    "9876541019878923569989413568943919985435433698767434989439899676779876678929875698765454969899893210",
    "9997632123969894697898954679659898976321012987654323678928678987989955568939984599854323456789989323",
    "9876543299858789986987895789798777895432123499543212569212567898998743456898765987543210167899878939",
    "9987654986745698965656789999987665489993234987654103488923456789987654567899896798674521234789767998",
    "8798769875435987854345898999896554376889359998763212567894678898799778678943987899795642345678957987",
    "7659879976329876543236987898789431285678998989654323679975989997678989989432198934976783658989349796",
    "8542989983212987621012976787678920124569987678965465789989899876566498996549239549989864567893298654",
    "7621095699345696532139865454567921234579878568996876791298798765432347897698949998799965878952149765",
    "9873234598766897643239874323658943765689766467789989890987659874321256998987998797678978989943239876",
    "8754345679897999654498765214745895876799654323567899939876541985432367899765987696567989799854345987",
    "9867456794998998765579986101236789989898965212356789923987430199843456998754898789435997698765667898",
    "9878587893499649877899874362345678996967896901234567899876521239756569876543789894329876599986798989",
    "1989698912987532988998765453656789765456789892345878934987432398767698765432656999210997989987969678",
    "0198789109876431299569898764567997674367998799456789321299543989898987654321239878921239878998954589",
    "3239898912987510123456929878698976543239895698967893210298759878989798796532398767892398768999123792",
    "4347987893497421234679219989789997632198754987898974321349899865679659987743998756779987657893234901",
    "5956976896596562345678998999899989545249843476789765432456987654598943499659879835567899546789349899",
    "9897985789989674566889987876999878967998932345678976545569876543467894598998754323456789435895498788",
    "8789874578978965677999976435698769879887821234569987987698765432348999987987643412578895323796997657",
    "7698765689569989788959865424987658998786540125689698998799896431239988675698432101678965434679876545",
    "6549876793458999899769976519876547897654321234789569899899865320129876554799543312487896595989987433",
    "6532987892667897979998752101987636789895432345895456789999965431298765343987698723456789989991096321",
    "5421298943456976367898943212396545679996543456789345999889996542987654212398987654678999878989985432",
    "7310129657567895456987654534987657789987786567895457898768989653498764301259798765789998767978976545",
    "5423298798678976569998865545698798999899897678989569987655678968569985422345699879899987656769898856",
    "6534569899889987678999876658789899998789998789878998765434678987699876543456789989959898545658789767",
    "7865689932997898989989987869895978987689899899765987654323567998989987676567897698969769535745678978",
    "8978798743456789699876598978954567996546789998754698765212356789878998789678976567898754321234599989",
    "9989987656567896567985459999543456789235678954843569872101245699965879893989298789999865432546789698",
    "5498998767689995499767345987652678990123567893232345983532358999894767992494349899899998743757896567",
    "7567899878999789987653237699864569432234678952101659876543467998743458989975956997788999654898965456",
    "8679997989998659898872123456965678945675789843212868987659579876562349678989899986567898765999654345",
    "9798986899987645799961012599876989656789897654346789298768989974301234567896798795456789876896543236",
    "9987845789986532987652143489987898967890929965467994399879998765212345698945987654324999987895432123",
    "9876534567899431298743235678998987898921919899978975987989989874323456789896799843219899998976543238",
    "9989423688987632349654346989239876789439898787899989876793468985434589897789987654598788899897665357",
    "9898912567898653759765458990198765678998775656789999965432349876556678915679998965987676756789875456",
    "6787893479999654569876569321997654567898664545679999876545678987677789434998989879898434345699986797",
    "5676789598998765678987678999876543456987543234567895987756789399899896599897878998764321256989597898",
    "4565678976789898799998889789985432367898994578978934599867893210989987989766767897654210135679698959",
    "3434569545678999899879995699954321238989987689989024567978964349878999876545656789654324345678959345",
    "2123678934567899999865634989876553345678998997692134598989765498767899985434545699798734576789943234",
    "3089799123456789398754323978987865467789439987543949989999876987657799994321235789987545787899894545",
    "4578943239768999299321019867998976567899321298659898878965989999545678965432545678998656898998789656",
    "7678954398978998978934998759899989989978930129898767567893498765434589876543456789989767999987679767",
    "8789766987899987869899876548789999896567891234999455456789987676523457987764567897679898989876568978",
    "9899899896789876756779965434678998765458932349894342345991096543212345698875678924569999876565467899",
    "1956998765699985437567896123578998654349693498789101257932987654901256989986789213498998965454356789",
    "2345679654987654323456789012667897653234589987678917348963498769892359878997994324987887894323235891",
    "9456998743298763212767894323458998769345679878567896457954569898789498768498985439876566789210157890",
    "8999899887349854324678996534567899898959798765456789767895699989698997654349976549957345994331268999",
    "7689789876598765435789989545689912987898987654345899878989989876567789743234989698743256789454359998",
    "6575678998989876576899878968798909876767898743236789989578976995423678994567898789654379896565467897",
    "5464567899567987687998769899987899965456999732105678993459985986312456789678989898785567997876579956",
    "4323456789459898788997656789976789896797898543214567892367896795401237898789879999876878998987678945",
    "3212577892399769899789545699865457789898987654623456901256789987214345999898768698987889899999789234",
    "4104689921987655945699876987676345699979798765434567894345678998325456898987654567898996799999890123",
    "5345699892498543234599989876543235789765639876546798965456799579499567987898965678979345989876921345",
    "5476899789698762123489996987674345698654521998687899876569895467988998976899976789765459878965432456",
    "6598997678999873035678945698765659789843210129798943987978954345976789345993297899976569769876543567",
    "9679876567898762124789236799876769897659434239899932198989769659865678956789998989897997656987794678",
    "8989987434987653235690127899989878998798945959999891019999898998754567897899879678789896545698895889",
    "7899876523498767345789634598797989899987899898789789199979987899763478989989765525696789234679876795",
    "6788953212369878456789545797656499789876598797689678989769876789874569879879954314345992123589987894",
    "5467899109457987667898776986545348679987987698994569879899965679865678965767895201299899239678998923",
    "6345678998968998989999889875431236568999876549013498768978954567976989424656999352989798998999999912",
    "1234899657899989696899999976320123479349995432124789757869893479989893212345798969976657987989989893",
    "2356789546789879545678998765431434689298789545235698543456789567899765601236987898765349896978976794",
    "5477895734345965434569129878562545699987678956345987432367899878999873213349876989543298765467895689",
    "6598984321239876723458934987673656789976598997659876543459921989498764323456965678943129876589934599",
    "7899876410156987814567895998788789899865467898767987654678910191239865695569876789621014998678923989",
    "8978984321269898923678909879899899987654398999898998765789991910445999989678987897433123459789219878",
    "9567896434398769798789219765956989998766589988999789876799989899566988778989798976545254569892101967",
    "2456987556987655649898998654345678949897678977987655987899876788979876567999659397654345678943239856",
    "3998999767896543234967998763234599932998799456798943298975635567898765456798943298785456989654598743",
    "9899989979987632123459876543123989891999892356989999349764323467987654348897892129896568998765987654",
    "8799877898976541012789987684539876789899921249878978959865934579598775457956789098987679109976798789",
    "6598766777897655123678998776898765678799210298765567899979895689439876568943899197998989298989899995",
    "5459655456789764234589659887987654345678921987554456789598789790123997899212348976879999987998987654",
    "2398543237897654345678943998987643234589439876432367892459698943239898954343467965467899876887896533",
    "1987652156789767457989892129798732156678945965421298901998567894598789965474567894356998765346789321",
    "0199864345678978567898789012679965248989659876562469219876456789987678896765678965487999653235678932",
    "1298765498789989679987678923459874359999878987673457998757345679996549789878789876598998743123469945",
    "2369876589892193989896567899569995967896989998754569876543254569875434678989899987929876543234567899",
    "5456987678954012399767436678998989898965499989895678985432123459989324459999989999212987664346778978",
    "6767898789999125498758325567987678789976569876986789876543012398764212368999878998901298795458989568",
    "7898979897878976597643214356798565678998798765497894998659123459653103457899769897892989987899593456",
    "8929469976867899989632101235976454589549987654398943239798934598543214567897656756789764398989432367",
    "9212398965658568976544312349894323878932198543219892124987995997654327678976542345679654219478949456",
    "2101987854343456799676423498784212567893989955456789239876789898765498789765431234792976501267898967",
    "3239876543212345678998568569653103456789878897697894349865478789876569897976542455891965415349987998",
    "4645989976101234989987679799743212345678956789989965497654365678987894956987653567999894323498876789",
    "6956799865423445897698789987654343456799345678978979984323234899998943245498767878998789444987655897",
    "9897899976567656789549899998765655569893234989866898775410125678989432101239878989987678976898543456",
    "8789988989689778996434999879876766678954347898655987654322236789876543234567989899876567897997652345",
    "7679867898789899654323498765987978789875656896543498767549997899997654345678998767985456949876543458",
    "4568989979893999843212998954598989899976767965432359989798789998998787456789878549876569434987674567",
    "3567899865912698764329876543319395989987898966321234599898656897899876567899965435989678923499787688",
    "4678987654323459965498765432101234579998999543210145678999542456789987878999874324598789436569898789"
};
// */
