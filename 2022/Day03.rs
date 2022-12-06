fn main() {
    print!("{} {} {}", 'a', ('B' as u8 - 1) , 'z' as u8);
   
    // // part 1
    // let mut sum_part_1 = 0;
    // for line in INPUT
    // {
    //     let firstPart: String = String::from(&line[0..(line.len()/2)]);
    //     let secondPart: String = String::from(&line[(line.len()/2)..line.len()]);
    //     // println!("Cut in ");
    //     // println!("{}", firstPart);
    //     // println!("{}", secondPart);
    //     for idx in 0..firstPart.len()
    //     {
    //         if secondPart.contains(firstPart.chars().nth(idx).unwrap())
    //         {
    //             sum_part_1 += get_count(firstPart.chars().nth(idx).unwrap());
    //             // println!("found {} => {}",firstPart.chars().nth(idx).unwrap(),get_count(firstPart.chars().nth(idx).unwrap()));
    //             break;
    //         }
    //     }
    // }
    // println!("Final sum for part one is {}", sum_part_1)
   
    // part 2
    let mut sum_part_2 = 0;
    for group in 0..INPUT.len()/3
    {
        let firstElf: String = String::from(INPUT[group*3]);
        let secondElf: String = String::from(INPUT[group*3+1]);
        let thirdElf: String = String::from(INPUT[group*3+2]);
       
        for idx in 0..firstElf.len()
        {
            if secondElf.contains(firstElf.chars().nth(idx).unwrap()) && thirdElf.contains(firstElf.chars().nth(idx).unwrap())
            {
                sum_part_2 += get_count(firstElf.chars().nth(idx).unwrap());
                println!("found {} => {}",firstElf.chars().nth(idx).unwrap(),get_count(firstElf.chars().nth(idx).unwrap()));
                break;
            }
        }
    }
    println!("Final sum for part one is {}", sum_part_2)
}

fn get_count(letter: char) -> i32 {
    let min_base_value: u8 = 'a' as u8 -1;
    let maj_base_value: u8 = 'A' as u8 -1 -26;
    let mut res :u8;
    if letter as u8 >= 'a' as u8
    {
        // println!("in min, letter is {} => {}, res would be {} - {}",letter, letter as u8, letter as u8, min_base_value);
        res = letter as u8 - min_base_value
    }
    else
    {
        // println!("in Maj, letter is {} => {}, res would be {} - {}",letter, letter as u8, letter as u8, maj_base_value);
        res = letter as u8 - maj_base_value
    }
    return res as i32
}

// // part one res is 157
// // part twp res is 70
// const INPUT: [&str; 6] = [
// "vJrwpWtwJgWrhcsFMMfFFhFp",         // repeate (p) which is 16
// "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL", // repeate (L) which is 38
// "PmmdzqPrVvPwwTWBwg",               // repeate (P) which is 42
// "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn",   // repeate (v) which is 22
// "ttgJtRGJQctTZtZT",                 // repeate (t) which is 20
// "CrZsJsPPZsGzwwsLwLmpwMDw"          // repeate (s) which is 19
// ];


// /*
// // part one res is 8233
// // part twp res is 2821
const INPUT: [&str; 300] = [
"GGVGlqWFgVfFqqVZGFlblJPMsDbbMrDMpDsJRn",
"LwzHtwdLHHwDrzPZzzsJbJ",
"wdLTBvSvHvZVGCjhfN",
"HsSSnZVHjjssZnJpSJjBHHWgQGcgqqQLQdQFqNgWgqGNDg",
"rmmRwrtfThtTrbCrGGGcLBDTqDBNQLdL",
"mwPrrbzPfwvbzhwMMnnjHnBjZlnzMM",
"gjjdMBgdqdTpJpBcjgRRRlqnvrqfnZtrtZDw",
"zHShWLhCszCWHVbVzQWCPtQvNZRwtfftfNnrnftlfR",
"PzPSssHbVhCLFMJFcMFJJMjdJw",
"ZqJdtpfpjmpJjpnwWdttTCDLLTQFNTzTzrcqrQqc",
"MsSlBGvBsSGGSlbGsCgggNTgzNLczFQNrNQVQcFzFF",
"sGHHSGllhvMGhSRGCjtjtjnjnnmHWpWWtJ",
"tMdjQlHPHsGjsCtsCpwwqfhfnnFMDMrpfD",
"SbNvWvBRJRWwFSgppgSrfg",
"RNcNbvzJRcVLRVzTRFLjdHCQttdZdPlHstPl",
"QWqgpdBflpHNCNWNHHPm",
"VVMbbJsLFVMhrMJMmRjFNHwHjjCTGSSRFj",
"mbMsZzsLmVhJZrcLcJhLMtnqvBnZdggplDffvlnlvnDn",
"prnNnsFnZpnBNdNtFrNnzNQQwTTQZqTHTQJQMwHDMDlZ",
"jgfgcSmbLmhmcPShghRdmwJTQjTlqGlJQJHqQqGHqQ",
"hRVhPfbCgbVggLVRSSmRhRPhrrrnCzzsvCvrnvFnNppsvBtd",
"QJLNDWSWQdLFFFhLdt",
"npHhHMsfsjpZjznRtmrMCdBwFBFrBdmt",
"HsjHqRRfnnHRsgfHffZspgzqDGQSWbQTDNGhQhSqNPhDWWbT",
"bsCmFDsGZCNsDmLDLZBSHSJTHnrZQMQSSQ",
"jqRpwvfqnnRQrftdBMHddB",
"phpchwpzjpvwRzwcsnlFsssPCCGzDlsD",
"rMqzVQfrfVZWZhTdRTQL",
"cgmtFtjFFJDDtFvSFRZdLlhpHZddmwTZWh",
"FbcSTtctcvFTJNgtJDGNPnCqMPMfMBfznGVsrMCq",
"wLJfGJJPZLBfwSLGHbqmhhDHHhFDzfhv",
"FsnpFjVjplTQCspNlCDbzhMMbqvMvsgmHDqb",
"lRdlTdTddllpRQFRltVVdFRcwrtrcWWcPrrWPrPSrZWLPc",
"VGVZhTppGTfPnJVJrFqbsmbSSshHqWqRHF",
"llzDCzlBLdNcCddlMMNBdCCtWHbFqFRRRsHjWtRwSWqbmjWm",
"NbcMBBvzzMQLCDBVTQQPVrPQPPZVPp",
"cdcgfmQdqlqhzzPjzfwpwf",
"GLBGBDvbvRzGwtnnmPpp",
"ZRCZBRFSRvLRLFvvbLLFQdHMTHTlQlNqNmqFlWdH",
"vzjzvHtcHvJcDStLLGSShCbbfF",
"MWFFTVZRMmMgdQdSQLwQrQwbGw",
"gFTmgmVZssRsWZRNzJlBHHnnJDvzNPlP",
"rHrvHpmHZfdGDDGGZd",
"cTlMsNhllMhGchNPCBlhMQgVDdgDSSWVbWVwRQwRSgbV",
"lnBjnNNTTMnCTcChPNhMvtzvFGLtJrjFtHHHzHJm",
"lgpdZZMmGVVzVZzt",
"HfHLrHqbPbzJJzRJJPTl",
"HsLWWbDqFrqlqfbsbDqDBncpgFmmvpnmmgpvdvjcdM",
"GpNVbTpJJNvMBMVvJTGvhnWQQScllnhhWlhVSznV",
"ZjswwHHLZzGnjWjSjl",
"sHdftLLtgLfwdtPmHtMbNpMTpNqGRbPvTqPv",
"sHSNNhNwsllGSGGlWSGWSsFrrVbQrdmFrVrrmnrHmrHr",
"QQMRZDDRcrcnmRcV",
"fJfCPMJCzTMZSGsWwsWBwqQf",
"HwQZZJsHdqqsdJQGRgCgVGgSqgpcGG",
"ljWWbnPhjBlGpCRCnScSGg",
"hrrztWlbPjltjMPSdJDZSsHttwsZwD",
"VzzbmzvpvNhvBDqc",
"QHSJSQGCwJCGrGQjjcgcBFhdgqdqFdDNNw",
"rCGJtZrHhhtLRsth",
"TMWwCLPpMTThrvtMRJjbjRvmJs",
"fDzcHFfSfFQfZzZRJbdmmqqssqtbSW",
"WWgGZglcllgPBBCBNVGPNr",
"wrwwhpTpbqhqrshrrfrFfwfzRJGdNJHNmcFzCCzCRJGzGR",
"vMggvjQvgPvQjVLMMPSZqWNJGCzcNGdcdzHPPzcmCzPz",
"qDZWvBZVfDhbTtrp",
"LpDvHdjVghnjbGrn",
"FBBBPwwlBlwSfFTWPHPWWhmgngmmnPnmbsngngbGrb",
"FwftBSCSfWCtwfVQDvHHCMVvdQLQ",
"ZrQpQlSpNlqQCVnQBmdDqmWDqmWWBDBB",
"HsZMsJvZzLMHTRwWhgDwmfDBgdhWdf",
"RZvTzJGzRjFrVNVjlQrS",
"mqjMwfqlSSPmSrlPhwhVpGRcppWcpcGRcGWv",
"ssJDJJNgZNDWrRWcRpvr",
"ZTsTnnsLJQgPnfMwmnMrfm",
"qsVBvZqWLdfbfvLj",
"mPNRgmHBBGQrCbSbrdfCCSbC",
"PlQTGcTTcgGFQQGPTGllpqMzwzpVJZwBMssZ",
"FWGcNRLRLhwJJQfV",
"nzbzlDBHSpTDbpDpzHwCqhqwJJghQqQMCCBw",
"JnzndzpmJFmNsrrFsc",
"gmRwwDwfnRDJgwZLFQFFNGNQrFBmFbbm",
"CCVHVWWThSrjVGvbNj",
"WpdqpplppHCWzlClMMTTZJcJsdscJLLdbDDfZDgL",
"VNtCCMDllpBqDvtdCczTSgjHlzGSHSGZTZ",
"hPFPsQhhFhLnbsRnLFssdzcHdsSHSSHgjzHG",
"QPWPQrPPmbdnbWLFPrrBVrVDBqqNMVwttDtBvD",
"PPNNRggwgRRgHBhDtwhTwbDs",
"SFGSFSMCJFMrcrCMSSsbtrTbbZhBvtHhrTHD",
"MFfSMpflQLQflfLjnLmddsLdddqq",
"RcgbcrrFscVrwZVCgVGGmHppNNndWnGdNqddqqNqND",
"jTlSTBSTjLTvlvjjPtvMLlhHnftphtDFNFqDnDHWNddn",
"QBMQvzzjzvJPjFQMmwZJrgmCCJVRVbbc",
"CzPJsWCpvsNszsJsNsHlDhMrrJGjhrRVhRGgDDjG",
"tFFdbqFLFdwctQdfVhjRRghTcrjVRTDW",
"bwQtFLdLBdFmwnHnWHPBNnHCnp",
"CNTstGNslRRRstlmNmmTZZqfFwtqgwqgfBPSwSWwqgWq",
"hpDbcHbpSrcgqqzhhWVfqg",
"DDcLDjbMjCSsZRNlMv",
"MhHMCMNbzbMHlcqmGmrmWc",
"tnPggdZPBPgdtttJpdnwVBnmqQcvlQrQlfGqmfWffBcqWD",
"VPPwPPLPwLGFGLzCbG",
"rqBcBmjHTGfPbcVgPG",
"dlDpsdshzlldlDvsWlWvLQbQBbfLFLbPvbBGQBgG",
"BlBznnRWzlphphBnhZjZtNNCNmrNqjCqHwHN",
"mQBvmvBmmLJvvrLtttQrfhGlcRGfRhVGWJVChlRG",
"MzPswTsbTPPsNgMNszgzMpbMfcRcGflVGRfWSpFRlWWWFhcC",
"bcPsTbgbbTTwNZzTZzvdjdjtQQndZvdrvdmZ",
"hQzTQJFFZJrcdcdZFFrGFSVWVRWRwRgRHVMWDCDSWc",
"lPmpNBnnnsNBnLnfbfnCDWMvwRvDCCMPwwHWvM",
"HpjmffNlnqqhddTddFZjGJ",
"BwsLFFbHLbVCSCSFbsbFLsJbqnTtZrRMHTZtrTrZTcRRRRTq",
"lGhNhpPmmhpztZTBrcpjRqpB",
"QPzdfzBQNgFJSCwsdLbS",
"ZsZsSBTgffSCqSSfrMnnMwjqmqmnnnqwMm",
"bbPPbzVclcPzGNlvzVtmnDBnQmtnQLBjJVLn",
"zPFGplGGvdPbHplcbzzvdlNBTThgRpCTCTfhfsCCsSRZhR",
"CVLSVCLVZRsHcnzSRpdZZRCdPlmcMWDDlPNqMqtDMmqPMlDt",
"TBnGjfQrQJjhfWlPPmPQDNlmlP",
"fjhhGvjvvrTTBhvTBTbvGVRLzVnbSRZpHddspHRzLs",
"DDtWjfRfftWMLzSQjzzhWjjwRVPHqFbBbZHVwZBFvFwZvZ",
"JGllgCJlJsrCGPrCNTPdslvZVVNVbvBqNbbpbbFHpBwZ",
"CcPdnCdmCJjfcftWhtSL",
"pgpfddDGHWzDNGNGpRCQjCTFHZZQFQjcRT",
"bJlhqmMvnlrRQFtTthPVhZ",
"lvbJrlJMBwfzGNTddB",
"wpbJGGZpsjvtdWvGWF",
"HqqhBhBqhhNQHTSHqqNzRHVPvTvddWrjtrjFvrvdTdVP",
"NRLCRzlqHQtNRBLzQllhhZcgbggwmLDZpsgssDpwwD",
"pDzFzJFcVMcWJFJFzpLBsqWLZssshsGLGbsS",
"wqHqfvnfrRwQtdQRthhBbBbZLhPLnBTGsh",
"CfQqlqvtfHNvMVmzmmMCFDMc",
"GcgpNHvcSNvpSLphdhsLdQTsdWThhQ",
"wwzttPrrhQswdhnT",
"tjJjMJRbRbjztmjtjbgcRsNlgglHpDFSlSvg",
"VVLvLqqPVlvcqLLdwLbHpzcHSsbRJppHbHpF",
"CfjjCNGmMWhWjhWHWb",
"ZmGZffggrDqZvZtlbTqL",
"TTmmhvBvvHWzHpsPpstpLVdwwsLb",
"qflfFgNctNcCnCCNDnfFFNDwrslwZbPswwZbJLJZbrlPLL",
"FgQDDcncStCgtqccjSDTHWMThvhTQMBQhWvWRG",
"SqhVghPccSBhgSBqWBFNQNsHQHMjCCQQWCwQHN",
"fLZftnlttcbbtZbZlpZtttQjwsCQjRwwRDQspMRMNNQs",
"TfLtvbJtZmlbTTTtlJbFvVqPSgBdPqPhFSGBcd",
"pPPNDptcqtpcDztLDhhngnnJgJTmJwNnwm",
"HVVCsSClHGBCHslWHbSCGGVngTrJwnnJnQRRBrhQhgJhdm",
"WTWWWsvVlvGbWCFvjDftPpjqZLLtDz",
"wWclwtDwRvflvffB",
"sMMsGdsSTMrJZNqczfdvhvnzCnfv",
"rspppMjMspSTSMpgLjcPFmwPLmPHwb",
"tCdSMHtHtRFHdWSSJQSgrrrnghTNJN",
"BGfcvDsfvsqcvqfGvfGnNLhggBNQJNJQmpgQJm",
"sGfQDPDZzfDZzclwDzwsDlfjtbdHClFRCMWjbMFMRFWbdj",
"pJNCcvqCccsVvFCpqsmvWJfCBWgSzBBRrrBRDDgDrSbbgQbQ",
"TMLnLjjffwfwGdjQjDDBjBrDtztRSb",
"MdPLGhHnMZhlPHHTFfZvVCpmmmcFcVFC",
"SwFMfCMRCdQDdMbmdFfdbbnlcVncVCcgLqWcNNnCcWlW",
"hPjQzzhGzhpPrtPJPpPHrVgnqVVncVVnNHlqVnncNB",
"ptjGrptztpthtrtJJhTsGwFDZZDQmSdfZSwsRZSwfZ",
"rSSWWCWrdllHWpjcnFNnRCNjQp",
"bGwwJqGVGbGJVVhgbBgttGmBQjFsMjpMcMnnMBcQFNnsssvv",
"bfthwmfJfgwwmmwZqVJPHNHSZHWzSlDPrdDdSH",
"nmJccvclcbwmlbbvVbvsHwJJPCPNCNPnLBhrBPPLBhLhBgBP",
"MdRGtdDRTqWDMqtMDtQDRWSdLLBsrhLgBCgrgCgNNLPBfNMf",
"dRZQdDdRRSQWGsjZmwzjmlzsZH",
"PBGGMrTQTrTBpPQpLpSlwjwfjtlnfwbmGttw",
"fCsJCWJcvRCtwwjbCl",
"NsqcsfcvDHFVDJvdLQTrpdTTzTPpHr",
"rltrwsBTlrfGZggGBLGGNN",
"jhMnRQJVphMnbhvQjDZNqqZDNTNHZVHGHq",
"MRvbhQRQQChpvbjvMSvQnMcsFsfwwmlCwFwWcTWwrmPc",
"DDvLLLBnvrzvbvbmtv",
"TMwRjTRMGCwGGwrjQQnmrQrrQdhZ",
"MJPFHFTwgCGqGqgJMGDfSWcsnBSccgVDlnpW",
"flzVzNrdLNLJzrGlfdlzjrQDgFTpDgDmmmgFmqFDQjQh",
"CbnBcsZnPZVSnwvVsZbRhhBDpgFphgmgDgTppq",
"ZWnsWSnncSZsntZCbsswwJMzdLzlMdNMLtMVfrllMt",
"ZffSgNfgJgGCHZcZrpHrNJTLhqvSLTqQnvVTLvzvLTjV",
"tWFtHMwlBlDqjjzjnqvvlV",
"DRMPDtWHPFDBFFwWMFBmFRPgZpJfsffNGJNrGcsprrsmfg",
"wRZRmpZmlPqZjzGrdrGq",
"bBhQQFPQbPDVNzVNzdGWNdrf",
"QFbcDcDbLHgHBPDFRsSSMtmvRttMpCLS",
"MpWJVVJMcWvpRShcwpLGflmqzSfNdfNLdQzN",
"CDBTtCgtbjgCRrBrPBTQqzflNqjGdLzzmqffzq",
"rFgnnBbttDTPtHCDPrPMnpwVJhJvMZvpMvppRZ",
"sWTTmpsfsWppPTTsTVZWHVVZNvVcdcJvdN",
"DjjBzjhRHvvvSzdc",
"rMBjjrjbjrGDlgMlMrGjBgRLPTTwHMsfnFwFQPMPMnmFFm",
"QRRbDjjmPzNQwFDNmrQmzCbVHrMhBVrJLJJfMGGLtfJBHh",
"dsWcsqqWSWvnWnWcWGPJLBqhLBqGhBJHHH",
"ZWnPWgWgPnlbCDDwmmDbRZ",
"nfPqqfLqQnfHBSqnzztQjVmjfGRWJNGRWsJWJfmJ",
"TTMlMMlFDMGVGRsVJH",
"CbDbFDbvgTFFwgTDlDprhlPSqBzSnPdLPtPPHgznQqBQ",
"fJmWVfHqjfjhZCQZ",
"NcNzBNvgszQmzjnthZQC",
"LsLsgBNFmFgTFgGBBgcdMdvPDPDJWrlpVbGpJWqHDlHJHD",
"SllDdvzgdFDdlPJvbFDDSzFScPTRTNcwfZRwRhcwwNnRZTtf",
"WBpWBCLGVpLjHrHGGVhZNwcTVcNhVnRcNZ",
"LHLQLspHWQGpWCHnBvdzDJFlqvdsqgSgqS",
"GcTctDMjMhpMDRjLsMMsfDWFfdPCFNbnCPnvCPgW",
"JmvwqlBwnmfdFPFP",
"SvZqHSZqqHZZZBlllBwSwsRsMHpLjpLsMGtsMspGRT",
"ClLnCLfClLVllfLLcQjLBCfCmSHVsttsmtsVStDNVdppdsSp",
"PFrRMbWqMRwFRqRSqwqvMvMsGtgsdmssrgNtdmpNdDGgdt",
"bwJbPWPwFFPFSczCZzZZCcfjBJ",
"MwmBmzwJQTcTmfPVfZPwhhwHPH",
"jlnrglFLvbrGRFGnvFZdNNFfPZddPThVhdPH",
"RjbjpgbnLGvpLgzBqBpmWmmzqTMS",
"FnsSpttPnPbNCFDtsPnFHQZTQZgcwgDDTfrfTHMZ",
"mRjzRzlvBvhjZrQmMMwfZZNN",
"ldzddlzLRlRWdhjdRLjhRWtJbJbNtJJpJPbCbGCWNG",
"wBwmNZBTmzzcVcmpzZqdMgPjnLSVlPgDPdbMdg",
"flJvGtHffHDddddbHjnb",
"RstrhfrhhRGFQtRhtftvQhvFZpsmpWwNlWqcWTccBNWswqNp",
"DPWhbzDlQLLlQbLDlLhPhLFNNJqCFGqnNJCCSCnGPnGN",
"wvwjtvtdwfssvSJgFFvGGSCFcp",
"mtdrZwwJsrtddrHRtZWbVThLlBzVTzhHQWhB",
"TsRRWctsTJMQZllggc",
"zDvhpbprgGvpvVlVQlZpQMJVlQ",
"rrrvFvGCDhDSrrrvChCgSstBNTSftWBjTdfWBN",
"JJdssBcLVGrgbBHWrH",
"QZTptvmvmlZpRDlMMMZCQvnjjFnrjWGFbjnrnFGWgZrz",
"TMRplDMggtwlppTlvhsJJqdcqwVPSSNcLd",
"JjTCCrcRvccPLmMP",
"NfGFPZlNnwBfPlbbbQZGqLHgzLghSmMBzSgvzmDMhv",
"ZfbnNQpQnZGlGlGpWTddjdTJdpRPTrCj",
"gWLblMMggdWsdRJlblMRMMqWDvPvcPPPccJPJVTZVZThmcDP",
"rQFfGfrCHrjnrtNTcPShTSPvvVLtmm",
"fQrCfLrpLHnCHwslqzqsslswzqRW",
"zpJtGlJPMPTlTjGJCDGCDljpdnvhhWnZnZnDwwmvnWDWWvdd",
"sHrVrSrRRRLNgLVBqSsZmWwvwcvwZjmwngmdbn",
"QsQQBrrLHTjPpTQzzP",
"JDlzHHzzptRDmbTMrrVQ",
"dRRNqnCBnmrQsVQQ",
"wFPCBNFgwjPwhgFNztftpJRPpzRvvHtZ",
"DlBhrDBPPwMWwhWchW",
"ntSqbbSJFJNqzVzjCfMvfSlSRWccRL",
"mVlHtNVtqldbJVmNHmdTTBBgrQQgGsPQdrDgsP",
"HWHNbBgvNLdcvQMnSf",
"wqqqVPDPhqwszFwrrszFfMdWthLcMdfhthSQfJSt",
"qVPVwTzFwFDpDrPDzDPFDPlCHjBGjTmZGjbWWGZBRTNjjH",
"GVgdWjllSqgjdgHqqlfmhwcpwCzhvZwMcScv",
"nsJQbLRQsNnzQDQQPPBbRBRhfZwpZcvwpvvmLCcvpcmfMM",
"DRJtnnRbBBnPztsrPzRBPbsFFHqqVrqggjFWqrgWjTGgFq",
"hhZJQPJFHGGlcWWslpNN",
"VwwwJjvwMtrCnwjDNDzlfscWszWW",
"nVStCrMqbVwqVqSqwnLPhTJFdRgJHZSFRLTP",
"vPgMbbRhhvMvNjjLWsWQsHQmHwBrmmBzww",
"tFctDnVFpppHVBTdzdTQwl",
"FtSFqSptfJCqqJStZCqDpDJMhvLLgLMgQgjgGZgGgMPLZg",
"zwsWgSGWLSVhPWhtLgLWhPVNQTmDrDQttZpdQtdpQDDQZQ",
"fjCHcvvjMDrppCQpVV",
"VMqRnVJMVLPzbRWhGh",
"mjRmzQlzDzNHWwDZ",
"FBfJBGqnnpfSVGnpJbJVfNtCsJHWZvrsNJCZrCNsvN",
"fZPBnfPqSBqdfpFbVnVSjgdcLLgRLjmgRhLLghlR",
"FSFnTcppdQtnnDhtzDfg",
"ZLGVmBLBVwZCVjjGqGhVwVVgzzbMDtNNvszMmMffNDDvtM",
"VZPJjBZVqBZZBjqwVqllpSTphhQFPShWSQcW",
"hTRdcLrCLgplLvBFGvlL",
"nZDZqzbDbDzRZtVNDzDWGwslsllBFpnlpGvJssFG",
"zbqjNWQVmVPrrRjRdRhS",
"VpNCbVHlHHZfflVfmchctqFcqQQjZmZM",
"WDSRGgsSvgJSRrnWgqQhmjBqmhqrtLqmQm",
"znSGTgDJnsDGzgwCwlpbCNwHzVtl",
"sTTTrpHFFFqTnQbbvfJdDzHHDLVV",
"CjMtgMgRvbPfjjvB",
"mhMvlhhWClvqshNTQQqsNN",
"tWFtFBzbwdFrpmdhdm",
"qTqDjJjJQQqMjTDLJjNqNqPNdmpcSmhdmhhmcrWZpdPGddcc",
"RjNQLJNTTJDDJRHHjQqnMWtlvvVvbtBvRVzgzgwgVg",
"CGdQjwdJrbBmpmZZZlRWcb",
"NgtMPVstgSzBLzhgzgLgDRlcmDWRmlZvcSmDSvvp",
"LhNsgPPLFPPsNzMhhVzPsGJBFqwQGfnqfQjdGdGfwr",
"CNbNdbzjCZpPNzjmzjsCMRJvnnMRGnsvJGRs",
"wrtdwTLWFcFWdFgwRRsnJGnGfTGJfMsq",
"FttcwgBtgVLgPldQSNZBzBpz",
"DjRZrrRmttRFDvDrFTZsnWnHVSTSSJVZJH",
"dNNhLqlLLqdCzfMMlCfSncTVVWcHdcVsVdSVnT",
"QqppMfzMfqWCwbRQrwFrrttQ",
"dwGjHrtjsdhfCHnPSpfMfDPpPDWS",
"lmNzzlLbFqcqNgzpWMSvbbvDQDGWDp",
"LBmglgmqBqmrwCGhCjVtBC",
"tvHgWZCCprlgpWglCtjPhLmPmhVdJFSzVzdJVmmQ",
"fBnTTnNNBnwfnNqcBbBBTbGJQQJhSSdQJJsmdJFSQGSmVV",
"cMcDwFbRfFRlHCRCZrrp",
"ZFWmgghzBgwgjWBzjzmRWWMmsVwnVrsdVdwNrrpnnVrPCnCP",
"GLLbtGqllctqvGJvSlQbJGsPnVdsdpsTPLsVppBCTVss",
"tJBStGSvctvDDfczmRgRZjzDjZmgzH",
"FMrLmsQQSWzCZBhpQJTQQZ",
"dPPVncVvPBJDCPhwJD",
"fvHbbVHvqnvvvBzgLbbGGmrbMr",
"mrZzrzqDrhZqDddSFrCGLLLPQPQBJPJJBnQq",
"TgbpGblWlMsjgWlgMfpNRgbRHHBnHHHtLpCJPCPBnBLJtQQL",
"sbTlblTlvRbbGblbFcdDzccVcDVvzzzd",
"zMzfzlGwSBMMSCMzhsPgfcPcfcbhjQPt",
"FHHqJVdJmFmdVrJdJppthscjGtqRPRcccgcQbR",
"rvNJJpLrvvLnJvNFFvZZZBWznBWGSDCMnCwz"
];
/**/ 
