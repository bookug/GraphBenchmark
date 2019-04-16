from http://snap.stanford.edu/data/email-Eu-core.html

NODEID DEPARTMENT
NODEID: id of the node (a member of the institute)
DEPARTMENT: id of the member's department (number in 0, 1, ..., 41)

The network was generated using email data from a large European research institution. We have anonymized information about all incoming and outgoing email between members of the research institution. There is an edge (u, v) in the network if person u sent person v at least one email. The e-mails only represent communication between institution members (the core), and the dataset does not contain incoming messages from or outgoing messages to the rest of the world.

The dataset also contains "ground-truth" community memberships of the nodes. Each individual belongs to exactly one of 42 departments at the research institute.

This network represents the "core" of the email-EuAll network, which also contains links between members of the institution and people outside of the institution (although the node IDs are not the same).

<table id="datatab" summary="Dataset statistics">
  <tr> <th colspan="2">Dataset statistics</th> </tr>
  <tr><td>Nodes</td> <td>1005</td></tr>
  <tr><td>Edges</td> <td>25571</td></tr>
  <tr><td>Nodes in largest WCC</td> <td>986 (0.981)</td></tr>
  <tr><td>Edges in largest WCC</td> <td>25552 (0.999)</td></tr>
  <tr><td>Nodes in largest SCC</td> <td>803 (0.799)</td></tr>
  <tr><td>Edges in largest SCC</td> <td>24729 (0.967)</td></tr>
  <tr><td>Average clustering coefficient</td> <td>0.3994</td></tr>
  <tr><td>Number of triangles</td> <td>105461</td></tr>
  <tr><td>Fraction of closed triangles</td> <td>0.1085</td></tr>
  <tr><td>Diameter (longest shortest path)</td> <td>7</td></tr>
  <tr><td>90-percentile effective diameter</td> <td>2.9</td></tr>
</table>