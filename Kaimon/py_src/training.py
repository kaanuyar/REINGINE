# -*- coding: utf-8 -*-
"""
Created on Tue Dec 24 03:08:09 2019

@author: mustafa
"""

import numpy as np
import torch


from utils import get_obs,load_models



#Load model
net=load_models("py_src/models/REINGINE-checkpoint.dat")
a=10
action=None
def step(state_dic):
    """
    Parameters
    ----------
    state_dic : dictionary
        current state of agent coming from environment

    Returns
    -------
    Action: angle

    """
    global net,a,action
    
    if a==10:
        state,done=get_obs(state_dic)
    
        state=sum(state,[])
    
        state_v = torch.tensor(np.array([state], copy=False))
        q_vals = net(state_v).data.numpy()[0]
        action = np.argmax(q_vals)
        a=0
    
    a+=1
    return action
    
    
    
    
    
    
    
    
