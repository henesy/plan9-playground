{ tot=0;
for (i=1; i<=NF; i++) tot+= $i;
print tot/NF; }