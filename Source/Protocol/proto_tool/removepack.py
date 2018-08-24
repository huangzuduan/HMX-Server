#!/usr/bin/python
# -*- coding: utf-8 -*-
#
import os, sys, re

Packagelist = []
SyntaxList = []

def clear_log():
	fp = open("build.log", 'wb');
	fp.write("");
	fp.close()
	return
	
def write_log(str):
	fp = open("build.log", 'a+');
	fp.write(str);
	fp.write("\n");
	fp.close()
	return
	
def DoPackage(file, input, output):
	global Packagelist
	filename = os.path.join(input, file)
	outname = os.path.join(output, file)
	write_log('--------do package filename:%s, outname：%s' %(filename, outname));
	
	out_fp = open(outname, 'rb');
	line = out_fp.readline();

	isEmpty = False
	if len(line) > 2:
		isEmpty = True;
	out_fp.close();
		
	fileopen = open(outname, 'rb').read();
	for package in Packagelist:
		packstr = package + '.'
		fileopen=fileopen.replace(packstr,"")
	if isEmpty:
		fileopen = '\n' + fileopen
	open(outname, 'wb').write(fileopen);
	
	return

def GetPackage(filename):
	global Packagelist
	fp = open(filename, 'rb')
	alllines=fp.readlines();
	fp.close()
	for eachline in alllines:
		if (re.match("package", eachline)):
			temp=eachline.replace("package","");
			temp=temp.replace(" ","");
			temp=temp.replace(";","");
			temp=temp.replace("\n","");
			temp=temp.replace("\r","");
			Packagelist.append(temp);
			return
	return

def DoSyntax(file, input, output):
	global Syntaxlist
	filename = os.path.join(input, file)
	outname = os.path.join(output, file)
	write_log('--------do package filename:%s, outname：%s' %(filename, outname));
	
	out_fp = open(outname, 'rb');
	line = out_fp.readline();

	isEmpty = False
	if len(line) > 2:
		isEmpty = True;
	out_fp.close();
		
	fileopen = open(outname, 'rb').read();
	for package in Syntaxlist:
		packstr = package + '.'
		fileopen=fileopen.replace(packstr,"")
	if isEmpty:
		fileopen = '\n' + fileopen
	open(outname, 'wb').write(fileopen);
	
	return
	
def GetSyntax(filename):
	global Syntaxlist
	fp = open(filename, 'rb')
	alllines=fp.readlines();
	fp.close()
	for eachline in alllines:
		if (re.match("syntax", eachline)):
			temp=eachline.replace("syntax","");
			temp=temp.replace(" ","");
			temp=temp.replace(";","");
			temp=temp.replace("\n","");
			temp=temp.replace("\r","");
			Syntaxlist.append(temp);
			return
	return
    

def read_proto(dirpath, outdir):
	if not os.path.isdir(dirpath):
		print '%s is not directory' % dirpath
		return
	if not os.path.isdir(outdir):
		print '%s is not outdir' % outdir
		return
	input = os.path.abspath(dirpath)
	output = os.path.abspath(outdir)
	write_log('----input:%s' %(input));
	write_log('----outdir:%s' %(output));
	
	os.chdir(input)
	for parent,dirnames,filenames in os.walk(output):
		for file in filenames:
			if (file.find('.proto') < 0) or (file.find('.svn') >= 0):
				continue
			src = os.path.join(input, file)
			if os.path.isfile(src):
				GetPackage(src)
				GetSyntax(src)
	
	#处理文件
	for parent,dirnames,filenames in os.walk(output):
		for file in filenames:
			if (file.find('.proto') < 0) or (file.find('.svn') >= 0):
				continue
			src = os.path.join(output, file)
			if os.path.isfile(src):
				DoPackage(file, input, output)
				DoSyntax(file, input, output)
	
	return

def main():
	if len(sys.argv) < 2:
		print 'Usage: <input_dir>' 
		sys.exit(1)
	clear_log();
	write_log('----------- start ------------');
	read_proto(sys.argv[1], sys.argv[2])
	global Packagelist
	global Syntaxlist
	print Packagelist
	print Syntaxlist
    

if __name__ == '__main__':
    main()
