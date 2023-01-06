rm -f ./flow_trace
rm -f ./cpu_trace
rm -f ./l2_trace
rm -f ./router_trace

../../cmp_org_huq_all_trace/sim-outorder \
    -redir:sim ./sim/sim.log \
    -redir:dump ./sim/dump \
    -flow_trace ./flow_trace \
    -cpu:trace ./cpu_trace \
    -L2:trace ./l2_trace \
    -router_trace ./router_trace \
    -config ../../config_mesh_ooo_xy_org \
    -max:barrier 0 -max:inst 1000000 `ls *.BNC`
