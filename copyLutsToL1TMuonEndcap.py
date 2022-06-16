#! /usr/bin/env python

import glob
import sys, os, fnmatch
import argparse
import getpass
import subprocess
import xml.etree.ElementTree as ET

eospath = "/store/user/jrotter/"
allowedModes = [15, 14, 13, 12, 11, 10, 9, 7, 6, 5, 3]
label = ""
xmlFileName = "f_logPtTarg_invlog2PtWgt_BDTG_AWB_Sq.weights.xml" #"f_logPtTarg_invPtWgt_BDTG_AWB_Sq.weights.xml" #"f_invPtTarg_invPtWgt_BDTG_AWB_Sq.weights.xml"
tags = ['Run2BitComp_NewSample_logPtTarg_invlog2PtWgt_1000MAXTRG_NoRPCDeWgt_e']
#dirs = ['v1p0', 'v1p1', 'v1p2']
dirs = ['v3p0']
targetVar = "logPt" #Options are: logPt, invPt, Pt

cmssw_directory = subprocess.Popen("echo $CMSSW_BASE", shell=True, stdout=subprocess.PIPE).stdout.read().strip('\n')
target_directory = cmssw_directory + "/src/L1Trigger-L1TMuonEndCap/pt_xmls" #"/src/L1Trigger/L1TMuonEndCap/data/pt_xmls"

for mode in allowedModes:
    print(mode)

    for itag in range(0,len(tags)):
        eoscommand = ('''eos root://cmseos.fnal.gov ls /store/user/jrotter | grep "EMTF_BDT_Train_Mode{}" | grep "{}" | grep "{}"'''.format(mode, label, tags[itag]))
        trainings = subprocess.Popen(eoscommand, shell=True, stdout=subprocess.PIPE).stdout.read().strip('\n')
        splittrainings = trainings.split('\n')
        #print(trainings.split('\n'))

        for training in splittrainings:
            #print("eos root://cmseos.fnal.gov ls /store/user/dildick/" + training)
            exec_string = ("xrdcp /eos/uscms/store/user/jrotter/" + training + "/" + xmlFileName + " " +
                           "{}/{}/".format(target_directory, dirs[itag]) +
                           xmlFileName.replace('.weights.xml', '_mode{}.weights.xml'.format(mode)))
            print(exec_string)
            os.system(exec_string)

            #continue

            ## split up the XML in 400 separate XML files
            tree = ET.parse('{}/{}/f_{}Targ_invlog2PtWgt_BDTG_AWB_Sq_mode{}.weights.xml'.format(target_directory, dirs[itag], targetVar,  mode)) #NEED TO CHANGE NAME OF Wgt
            root = tree.getroot()
            weights= root.find('Weights')

            for itree in range(0,len(weights)):
                iweight = weights[itree]
                mydata = ET.tostring(iweight)
                myfile = open("{}/{}/{}/{}.xml".format(target_directory, dirs[itag], mode, itree), "w")
                myfile.write("""<?xml version="1.0"?>\n""")
                myfile.write(mydata)
                myfile.close()
